#ifndef CORE_H
#define CORE_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stddef.h>
#include <math/linear.h>

#define UNUSED(x) (void)(x)

typedef struct {
    uint64_t hash;
    uint32_t uvs; 
} block_texture_pair;

typedef struct {
    uint64_t hash;
    uint32_t atlas;
} block_atlas_pair;

typedef struct mesh {
    uint32_t vbo, vao, ebo;
    size_t indices;
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

    block_texture_pair *block_textures;
    block_atlas_pair *block_atlases;

    lua_State *L;

    meshes_t *meshes;
    size_t texture_count, atlas_count;
    uint32_t texture_array;
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
