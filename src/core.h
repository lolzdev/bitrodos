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

    lua_State *L;

    meshes_t *meshes;
    float delta_time;
} state_t;

typedef enum direction {
    NORTH, // -z
    SOUTH, // +z
    WEST, // -x
    EAST, // +x
    TOP, // +y
    BOTTOM, // -y
} direction_t;

#endif
