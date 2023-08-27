#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include <core.h>
#include <GLFW/glfw3.h>
#include <log.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void init_input(state_t *state);

int is_key_down(int key);
int l_is_key_down(lua_State *L);

#endif
