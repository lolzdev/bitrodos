#ifndef LINEAR_H
#define LINEAR_H

#include <stdlib.h>
#include <string.h>
#include <test.h>

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

typedef float mat2[2][2];
typedef float mat3[3][3];
typedef float mat4[4][4];

float vec2_dot(vec2 a, vec2 b);
float vec3_dot(vec3 a, vec3 b);
float vec4_dot(vec4 a, vec4 b);

void vec3_cross(vec3 dest, vec3 a, vec3 b);

#endif
