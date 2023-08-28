#ifndef REGISTRY_H
#define REGISTRY_H

#include <stdint.h>
#include <core.h>
#include <hash.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <glad/gl.h>
#include <log.h>
#include <rendering/text.h>
#include <ft2build.h>
#include FT_FREETYPE_H

void init_registries(state_t *state);

void register_block(const char *namespace, const char *name, uint64_t *textures, state_t *state);
uint32_t get_block_metadata(const char *namespace, const char *name, state_t *state, uint64_t *textures);

void register_font(const char *namespace, const char *name, state_t *state);
void get_font_metadata(const char *namespace, const char *name, state_t *state, char_metadata_pair *chars);

int l_register_block(lua_State *L);
int l_register_font(lua_State *L);

#endif
