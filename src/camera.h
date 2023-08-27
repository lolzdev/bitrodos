#ifndef CAMERA_H
#define CAMERA_H

#include <math/linear.h>
#include <core.h>
#include <glad/gl.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void camera_create(camera_t *dest, vec3 position, float yaw, float pitch);
void camera_update(camera_t *camera);
void camera_resize(camera_t *camera, uint32_t width, uint32_t heigth);
void camera_matrices(camera_t *camera, mat4 view, mat4 perspective);
void camera_move(camera_t *camera, direction_t direction, float delta_time);
void camera_rotate(camera_t *camera, float delta_x, float delta_y);
void camera_use(camera_t *camera, uint32_t shader);

camera_t *check_camera(lua_State *L, uint32_t arg);

int l_camera(lua_State *L);
int l_camera_update(lua_State *L);
int l_camera_resize(lua_State *L);
int l_camera_move(lua_State *L);
int l_camera_rotate(lua_State *L);
int l_camera_use(lua_State *L);

static const luaL_Reg camera_m[] = {
    {"update", l_camera_update},
    {"resize", l_camera_resize},
    {"move", l_camera_move},
    {"rotate", l_camera_rotate},
    {"use", l_camera_use},
    {NULL, NULL}
};

#endif
