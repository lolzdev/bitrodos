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

int l_camera_create(lua_State *L);

#endif
