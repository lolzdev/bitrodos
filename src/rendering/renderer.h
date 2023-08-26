#ifndef RENDERER_H
#define RENDERER_H

#include <glad/gl.h>
#include <stdlib.h>
#include <string.h>
#include <log.h>

typedef struct mesh {
    uint32_t vbo, vao, ebo;
} mesh_t;

typedef struct meshes {
    mesh_t *mesh;
    struct meshes *next;
} meshes_t;

typedef struct render_state {
    uint32_t shader;
    meshes_t *meshes;
} render_state_t;

extern render_state_t RENDER_STATE;

void create_mesh(mesh_t *mesh, float *vertices, size_t vertices_len, uint32_t *indices, size_t indices_len);
meshes_t *push_mesh(meshes_t *head, mesh_t mesh);
void destroy_meshes(meshes_t *head);
mesh_t *get_mesh(meshes_t *head, uint32_t index);
void remove_mesh(meshes_t *head, uint32_t index);
void render_loop();

#endif
