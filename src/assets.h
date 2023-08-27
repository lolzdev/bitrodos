#ifndef ASSETS_H
#define ASSETS_H

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <glad/gl.h>
#include <log.h>
#include <stb_image.h>
#include <core.h>
#include <hash.h>
#include <stb_image_write.h>
#include <dirent.h>

char *read_file(char *filename);
uint32_t load_shader_module(const char *namespace, const char *name, uint32_t type);
uint32_t load_shader_program(const char *namespace, const char *vertex_name, const char *fragment_name);
uint32_t create_block_atlas(const char *namespace, state_t *state);
void remove_extension(char *filename);

uint32_t get_texture(char *id, float *uvs);

#endif
