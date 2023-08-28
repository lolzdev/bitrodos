#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <assets.h>

char *read_file(char *filename)
{
    char * buffer = 0;
    long length;
    FILE * f = fopen (filename, "rb");

    if (f) {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = (char *) malloc (length+1);
        if (buffer) {
            fread (buffer, 1, length, f);
        }
        fclose (f);
    }

    buffer[length] = '\0';
    return buffer;
}

uint32_t load_shader_module(const char *namespace, const char *name, uint32_t type)
{
    size_t path_len = strlen(name) + strlen(namespace) + 16;
    char *path = (char *) malloc(path_len);
    sprintf(path, "mods/%s/assets/shaders/%s", namespace, name);
    const char *source = read_file(path);
    uint32_t shader = 0;

    if (source) {
        shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        int  success;
        char info_log[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, info_log);
            error("Failed to compile shader module. [%s];[%s]", info_log, name);
        }
    } else {
        error("Failed loading shader module, can't read source. [%s]", name);
    }

    free(path);
    return shader;
}

uint32_t load_shader_program(const char *namespace, const char *vertex_name, const char *fragment_name)
{
    uint32_t vertex_module = load_shader_module(namespace, vertex_name, GL_VERTEX_SHADER);
    uint32_t fragment_module = load_shader_module(namespace, fragment_name, GL_FRAGMENT_SHADER);

    uint32_t program = glCreateProgram();
    glAttachShader(program, vertex_module);
    glAttachShader(program, fragment_module);
    glLinkProgram(program);

    int  success;
    char info_log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        error("Failed to link shader program. [%s]", info_log);
    }

    glDeleteShader(vertex_module);
    glDeleteShader(fragment_module);

    return program;
}

void create_block_atlas(const char *namespace, uint32_t current_tex, state_t *state)
{
    size_t path_len = strlen(namespace) + 30;
    char *path = (char *) malloc(path_len);
    sprintf(path, "mods/%s/assets/textures/blocks/", namespace);

    struct dirent *entry = NULL;
    DIR *dp = NULL;
    
    unsigned char *atlas = (unsigned char *) malloc(sizeof(char) * 4 * 16 * 16 * 256);
    size_t atlas_width = 256;
    memset(atlas, 0, sizeof(char) * 4 * 16 * 16 * 256);
    size_t atlas_x = 0, atlas_y = 0;
    int resized = 0;

    dp = opendir(path);
    if (dp != NULL) {
        while ((entry = readdir(dp))) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                state->texture_count++;
        }
    }

    if (!state->block_textures)
        state->block_textures = malloc(sizeof(block_texture_pair) * state->texture_count);
    else
        state->block_textures = realloc(state->block_textures, sizeof(block_texture_pair) * state->texture_count);

    closedir(dp);

    dp = opendir(path);
    if (dp != NULL) {
        uint32_t current_id = 0;
        while ((entry = readdir(dp))) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                free(path);
                path_len = strlen(namespace) + strlen(entry->d_name) + 30;
                path = (char *) malloc(path_len);
                sprintf(path, "mods/%s/assets/textures/blocks/%s", namespace, entry->d_name);

                int width, height, channels;
                unsigned char *data = stbi_load(path, &width, &height, &channels, 4);
                if (width != 16 && !resized) {
                    resized = 1;
                    atlas = realloc(atlas, sizeof(char) * 4 * width * width * 256);
                    atlas_width = width * 16;
                    memset(atlas, 0, sizeof(char) * 4 * width * width * 256);
                } 

                remove_extension(entry->d_name);
                for (size_t i=0; i < state->texture_count; i++) {
                    if (!state->block_textures[i].hash) {
                        size_t id_len = strlen(entry->d_name) + strlen(namespace) + 2;
                        char *id = malloc(sizeof(char) * id_len);
                        sprintf(id, "%s:%s", namespace, entry->d_name);
                        state->block_textures[i].hash = hash((uint8_t *)id);
                        state->block_textures[i].uvs = current_id;
                        free(id);
                    }
                }

                for (size_t data_y = 0; data_y < (size_t) width; data_y++) {
                    for (size_t data_x = 0; data_x < (size_t) height; data_x++) {
                        size_t from = (data_y * width * 4) + (data_x * 4);
                        size_t to = ((atlas_y + data_y) * 256 * 4) + ((atlas_x + data_x) * 4);

                        for(int channel = 0; channel < 4; ++channel) {
                            atlas[to + channel] = data[from + channel];
                        }
                    }
                } 

                atlas_x += width;

                if (atlas_x > atlas_width - width) {
                    atlas_x = 0;
                    atlas_y += height;
                }

                stbi_image_free(data);
                current_id++;
            }
        }
    }

    closedir(dp);

    uint32_t atlas_texture = current_tex;
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, current_tex, atlas_width, atlas_width, 1, GL_RGBA, GL_UNSIGNED_BYTE, atlas);

    current_tex++;
    stbi_image_free(atlas);

    state->atlas_count++;
    if (!state->block_atlases) {
        state->block_atlases = malloc(sizeof(block_atlas_pair));
    } else {
        state->block_atlases = realloc(state->block_atlases, sizeof(block_atlas_pair) * state->atlas_count);
    }

    state->block_atlases[state->atlas_count-1].hash = hash((uint8_t *)namespace);
    state->block_atlases[state->atlas_count-1].atlas = atlas_texture;

    free(path);
}

void remove_extension(char *filename)
{
    char c;

    while ((c = *filename)) {
        if (c == '.') {
            *filename = '\0';
        }

        filename++;
    }
}

uint32_t get_texture(char *namespace, char *name, uint32_t *uvs, state_t *state)
{
    if (uvs) {
        size_t id_len = strlen(name) + strlen(namespace) + 2;
        char *id = malloc(sizeof(char) * id_len);
        sprintf(id, "%s:%s", namespace, name);

        for (size_t i=0; i < state->texture_count; i++) {
            if (state->block_textures[i].hash == hash((uint8_t *) id))
                *uvs = state->block_textures[i].uvs;
        }

        free(id);
    }

    for (size_t i=0; i < state->atlas_count; i++) {
        if (state->block_atlases[i].hash == hash((uint8_t *) namespace))
            return state->block_atlases[i].atlas;
    }

    return 0;
}

void load_textures(state_t *state)
{
    uint32_t mods = 0;
    struct dirent *entry = NULL;
    DIR *dp = NULL;
    
    dp = opendir("mods");
    if (dp != NULL) {
        while ((entry = readdir(dp))) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) mods++;
        }
    }

    closedir(dp);

    uint32_t current_tex = 0;
    uint32_t array_texture;
    glGenTextures(1, &array_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, array_texture);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 256, 256, mods);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    dp = opendir("mods");
    if (dp != NULL) {
        while ((entry = readdir(dp))) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                create_block_atlas(entry->d_name, current_tex, state);
            }
        }
    }

    closedir(dp);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    state->texture_array = array_texture;
}
