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

uint32_t load_shader_module(char *name, uint32_t type)
{
    size_t path_len = strlen(name) + 16;
    char *path = (char *) malloc(path_len);
    sprintf(path, "assets/shaders/%s", name);
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

uint32_t load_shader_program(char *vertex_name, char *fragment_name)
{
    uint32_t vertex_module = load_shader_module(vertex_name, GL_VERTEX_SHADER);
    uint32_t fragment_module = load_shader_module(fragment_name, GL_FRAGMENT_SHADER);

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
