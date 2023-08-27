#include <input.h>

static state_t *STATE;
static int keys_down[GLFW_KEY_LAST];

void init_input(state_t *state)
{
   STATE = state; 
}

void mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in)
{
    UNUSED(window);

    hook_node_t *hooks = STATE->cursor_hooks;
    while (hooks) {
        if (hooks->ref == LUA_NOREF) {
            hooks = hooks->next;
            continue;
        }

        lua_rawgeti(STATE->L, LUA_REGISTRYINDEX, hooks->ref);
        lua_pushnumber(STATE->L, x_pos_in);
        lua_pushnumber(STATE->L, y_pos_in);
        lua_pushnumber(STATE->L, STATE->delta_time);
        if (lua_pcall(STATE->L, 3, 0, 0) != LUA_OK) error("A lua cursor hook has thrown an error: %s", lua_tostring(STATE->L, -1));
        hooks = hooks->next;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    UNUSED(window);

    if (action == GLFW_PRESS) keys_down[key] = 1;
    if (action == GLFW_RELEASE) keys_down[key] = 0;

    hook_node_t *hooks = STATE->key_hooks;
    while (hooks) {
        if (hooks->ref == LUA_NOREF) {
            hooks = hooks->next;
            continue;
        }

        lua_rawgeti(STATE->L, LUA_REGISTRYINDEX, hooks->ref);
        lua_pushinteger(STATE->L, key);
        lua_pushinteger(STATE->L, scancode);
        lua_pushinteger(STATE->L, action);
        lua_pushinteger(STATE->L, mods);
        lua_pushnumber(STATE->L, STATE->delta_time);
        if (lua_pcall(STATE->L, 5, 0, 0) != LUA_OK) error("A lua key hook has thrown an error: %s", lua_tostring(STATE->L, -1));
        hooks = hooks->next;
    }
}

int is_key_down(int key)
{
    return keys_down[key];
}

int l_is_key_down(lua_State *L)
{
    lua_pushboolean(L, is_key_down(luaL_checkinteger(L, 1)));
    return 1;
}
