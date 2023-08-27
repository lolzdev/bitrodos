#ifndef RENDERING_LUA_H
#define RENDERING_LUA_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <assets.h>
#include <glad/gl.h>

int l_load_shader(lua_State *L);
int l_use_shader(lua_State *L);

#endif
