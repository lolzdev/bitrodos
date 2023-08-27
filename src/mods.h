#ifndef MODS_H
#define MODS_H

#include <assets.h>
#include <dirent.h>
#include <log.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
#include <rendering/lua.h>
#include <stdlib.h>
#include <rendering/renderer.h>
#include <core.h>

int l_add_hook(lua_State *L);

static const luaL_Reg module_graphics[] = {
    {"load_shader", l_load_shader},
    {"use_shader", l_use_shader},
    {NULL, NULL}
};

static const luaL_Reg module_system[] = {
    {"add_hook", l_add_hook},
    {NULL, NULL}
};

static const luaL_Reg module_log[] = {
    {"info", l_info},
    {"warn", l_warn},
    {"error", l_error},
    {NULL, NULL}
};

void load_mods(state_t *state);
void load_mod(char *name, lua_State *L);

int l_require(lua_State *L);

#endif
