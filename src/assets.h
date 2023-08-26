#ifndef ASSETS_H
#define ASSETS_H

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <glad/gl.h>
#include <log.h>

char *read_file(char *filename);
uint32_t load_shader_module(char *name, uint32_t type);
uint32_t load_shader_program(char *vertex_name, char *fragment_name);

#endif
