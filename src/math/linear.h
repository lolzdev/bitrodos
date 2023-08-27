#ifndef LINEAR_H
#define LINEAR_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


#define PI 3.14159265358979323846
#define RAD(deg) deg * (PI / 180.0f)
#define DEG(rad) rad * (180.0f / PI)

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

typedef float mat2[2][2];
typedef float mat3[3][3];
typedef float mat4[4][4];

float vec2_dot(vec2 a, vec2 b);
float vec3_dot(vec3 a, vec3 b);
float vec4_dot(vec4 a, vec4 b);

void vec2_sub(vec2 dest, vec2 a, vec2 b);
void vec3_sub(vec3 dest, vec3 a, vec3 b);
void vec4_sub(vec4 dest, vec4 a, vec4 b);

void vec2_add(vec2 dest, vec2 a, vec2 b);
void vec3_add(vec3 dest, vec3 a, vec3 b);
void vec4_add(vec4 dest, vec4 a, vec4 b);

void vec3_cross(vec3 dest, vec3 a, vec3 b);

void vec2_normalize(vec2 dest, vec2 a);
void vec3_normalize(vec3 dest, vec3 a);
void vec4_normalize(vec4 dest, vec4 a);

void vec2_scale(vec2 dest, vec2 a, float scale);
void vec3_scale(vec3 dest, vec3 a, float scale);
void vec4_scale(vec4 dest, vec4 a, float scale);

void mat4_perspective(mat4 dest, float fov, float aspect, float near, float far);
void mat4_lookat(mat4 dest, vec3 eye, vec3 target, vec3 up);

int l_vec3(lua_State *L);
int l_vec3_add(lua_State *L);
int l_vec3_sub(lua_State *L);
int l_vec3_mul(lua_State *L);
int l_vec3_div(lua_State *L);
int l_vec3_negate(lua_State *L);
int l_vec3_equal(lua_State *L);
int l_vec3_tostring(lua_State *L);
int l_vec3_index(lua_State *L);
int l_vec3_newindex(lua_State *L);

static const luaL_Reg vec3_m[] = {
    {"__add", l_vec3_add},
    {"__eq", l_vec3_equal},
    {"__sub", l_vec3_sub},
    {"__unm", l_vec3_negate},
    {"__mul", l_vec3_mul},
    {"__div", l_vec3_mul},
    {"__tostring", l_vec3_tostring},
    {"__index", l_vec3_index},
    {"__newindex", l_vec3_newindex},
    {NULL, NULL}
};

#endif
