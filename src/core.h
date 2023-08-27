#ifndef CORE_H
#define CORE_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stddef.h>
#include <math/linear.h>

#define UNUSED(x) (void)(x)

typedef struct mesh {
    uint32_t vbo, vao, ebo;
} mesh_t;

typedef struct meshes {
    mesh_t *mesh;
    struct meshes *next;
} meshes_t;

typedef struct hook_node {
    int ref;
    struct hook_node *next;
} hook_node_t;

typedef struct camera {
    vec3 position, front, up, right;
    float yaw, pitch, speed, sensitivity;
    uint32_t width, heigth;
} camera_t;

typedef struct camera_node {
    camera_t *camera;
    struct camera_node *next;
} camera_node_t;

typedef struct state {
    hook_node_t *render_hooks;
    hook_node_t *pre_init_hooks;
    hook_node_t *key_hooks;
    hook_node_t *cursor_hooks;
    hook_node_t *tick_hooks;
    hook_node_t *resize_hooks;

    lua_State *L;

    meshes_t *meshes;
    float delta_time;
} state_t;

typedef enum direction {
    NORTH = 0, // -z
    SOUTH = 1, // +z
    WEST = 2, // -x
    EAST = 3, // +x
    TOP = 4, // +y
    BOTTOM = 5, // -y
} direction_t;

#endif
