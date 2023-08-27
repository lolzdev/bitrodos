#ifndef RENDERER_H
#define RENDERER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>
#include <log.h>
#include <camera.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <mods.h>
#include <core.h>

void create_mesh(mesh_t *mesh, float *vertices, size_t vertices_len, uint32_t *indices, size_t indices_len);
meshes_t *push_mesh(meshes_t *head, mesh_t mesh);
void destroy_meshes(meshes_t *head);
mesh_t *get_mesh(meshes_t *head, uint32_t index);
void remove_mesh(meshes_t *head, uint32_t index);
void render_loop(state_t *state);

#endif
