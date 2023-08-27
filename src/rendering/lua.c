#include <rendering/lua.h>

int l_load_shader(lua_State *L)
{
    const char *namespace = lua_tostring(L, 1);
    if (!namespace) return luaL_error(L, "expected type `string` as parameter #1");
    const char *vertex = lua_tostring(L, 2);
    if (!vertex) return luaL_error(L, "expected type `string` as parameter #2");
    const char *fragment = lua_tostring(L, 3);
    if (!fragment) return luaL_error(L, "expected type `string` as parameter #3");
    
    lua_pushinteger(L, load_shader_program(namespace, vertex, fragment));

    return 1; 
}

int l_use_shader(lua_State *L)
{
    int isnum = 0;
    uint32_t program = lua_tointegerx(L, 1, &isnum);

    if (!isnum) return luaL_error(L, "expected type `integer` as parameter #1");

    glUseProgram(program);

    return 0;
}
