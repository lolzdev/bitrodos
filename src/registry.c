#include <registry.h>

static state_t *STATE;

void init_registries(state_t *state)
{
    STATE = state;
}

void register_block(const char *namespace, const char *name, uint64_t *textures, state_t *state)
{
    state->block_registry_size++;
    if (!state->block_registry)
        state->block_registry = malloc(sizeof(block_metadata_pair));
    else
        state->block_registry = realloc(state->block_registry, sizeof(block_metadata_pair) * state->block_registry_size);

    size_t id_len = strlen(name) + strlen(namespace) + 2;
    char *id = malloc(sizeof(char) * id_len);
    sprintf(id, "%s:%s", namespace, name);
    state->block_registry[state->block_registry_size-1].hash = hash((uint8_t *) id);
    state->block_registry[state->block_registry_size-1].id = state->block_registry_size;
    state->block_registry[state->block_registry_size-1].textures = malloc(sizeof(uint64_t) * 6);
    memcpy(state->block_registry[state->block_registry_size-1].textures, textures, sizeof(uint64_t) * 6);

    free(id);
}

uint32_t get_block_metadata(const char *namespace, const char *name, state_t *state, uint64_t *textures)
{
    size_t id_len = strlen(name) + strlen(namespace) + 2;
    char *id = malloc(sizeof(char) * id_len);
    sprintf(id, "%s:%s", namespace, name);

    for (size_t i=0; i < state->block_registry_size; i++) {
        if (state->block_registry[i].hash == hash((uint8_t *) id)) {
            if (textures)
                memcpy(textures, state->block_registry[i].textures, sizeof(uint64_t) * 6);
            return state->block_registry[i].id;
        }
    }

    free(id);

    return 0;
}

int l_register_block(lua_State *L)
{
    const char *namespace = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);

    uint64_t textures[6];

    lua_pushinteger(L, 1);
    lua_gettable(L, 3);
    const char *texture_north = lua_tostring(L, -1);
    if (!texture_north) return luaL_error(L, "expected `string` for texture identifier");
    lua_pushinteger(L, 2);
    lua_gettable(L, 3);
    const char *texture_south = lua_tostring(L, -1);
    if (!texture_south) return luaL_error(L, "expected `string` for texture identifier");
    lua_pushinteger(L, 3);
    lua_gettable(L, 3);
    const char *texture_west = lua_tostring(L, -1);
    if (!texture_west) return luaL_error(L, "expected `string` for texture identifier");
    lua_pushinteger(L, 4);
    lua_gettable(L, 3);
    const char *texture_east = lua_tostring(L, -1);
    if (!texture_east) return luaL_error(L, "expected `string` for texture identifier");
    lua_pushinteger(L, 5);
    lua_gettable(L, 3);
    const char *texture_top = lua_tostring(L, -1);
    if (!texture_top) return luaL_error(L, "expected `string` for texture identifier");
    lua_pushinteger(L, 6);
    lua_gettable(L, 3);
    const char *texture_bottom = lua_tostring(L, -1);
    if (!texture_bottom) return luaL_error(L, "expected `string` for texture identifier");

    textures[0] = hash((uint8_t *) texture_north);
    textures[1] = hash((uint8_t *) texture_south);
    textures[2] = hash((uint8_t *) texture_west);
    textures[3] = hash((uint8_t *) texture_east);
    textures[4] = hash((uint8_t *) texture_top);
    textures[5] = hash((uint8_t *) texture_bottom);

    register_block(namespace, name, textures, STATE);

    return 0;
}

void register_font(const char *namespace, const char *name, state_t *state)
{
    state->font_registry_size++;
    if (!state->font_registry)
        state->font_registry = malloc(sizeof(font_metadata_pair));
    else
        state->font_registry = realloc(state->font_registry, sizeof(font_metadata_pair) * state->font_registry_size);

    size_t id_len = strlen(name) + strlen(namespace) + 2;
    char *id = malloc(sizeof(char) * id_len);
    sprintf(id, "%s:%s", namespace, name);
    state->font_registry[state->font_registry_size-1].hash = hash((uint8_t *) id);
    free(id);

    size_t file_len = strlen(name) + strlen(namespace) + 23;
    char *file_name = malloc(sizeof(char) * file_len);
    sprintf(file_name, "mods/%s/assets/fonts/%s.ttf", namespace, name);
    FT_Face face = create_font_face(file_name);
    free(file_name);

    FT_Set_Pixel_Sizes(face, 0, 48);

    for (uint32_t c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            error("Failed to build glyph %c for font %s:%s", c, namespace, name);
            continue;
        }

        uint32_t texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        char_metadata_pair ch = {0};
        ch.texture = texture;
        ch.width = face->glyph->bitmap.width;
        ch.height = face->glyph->bitmap.rows;
        ch.delta_x = face->glyph->bitmap_left;
        ch.delta_y = face->glyph->bitmap_top;
        ch.advance = face->glyph->advance.x;

        state->font_registry[state->font_registry_size-1].chars[c] = ch;
    }

}

void get_font_metadata(const char *namespace, const char *name, state_t *state, char_metadata_pair *chars)
{
    size_t id_len = strlen(name) + strlen(namespace) + 2;
    char *id = malloc(sizeof(char) * id_len);
    sprintf(id, "%s:%s", namespace, name);

    for (size_t i=0; i < state->font_registry_size; i++) {
        if (state->font_registry[i].hash == hash((uint8_t *) id)) {
            if (chars)
                memcpy(chars, state->font_registry[i].chars, sizeof(char_metadata_pair) * 128);
        }
    }

    free(id);
}

int l_register_font(lua_State *L)
{
    const char *namespace = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);

    register_font(namespace, name, STATE);

    return 0;
}
