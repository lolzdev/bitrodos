#include <math/linear.h>

float vec2_dot(vec2 a, vec2 b)
{
    float result = 0.0f;
    for (int i=0; i<2; i++) {
        result += a[i] * b[i];
    }

    return result;
}

float vec3_dot(vec3 a, vec3 b)
{
    float result = 0.0f;
    for (int i=0; i<3; i++) {
        result += a[i] * b[i];
    }

    return result;
}

float vec4_dot(vec4 a, vec4 b)
{
    float result = 0.0f;
    for (int i=0; i<4; i++) {
        result += a[i] * b[i];
    }

    return result;
}

void vec3_cross(vec3 dest, vec3 a, vec3 b)
{
    vec3 res = {0};
    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
    memcpy(dest, res, sizeof(vec3));
}

void mat4_perspective(mat4 dest, float fov, float aspect, float near, float far)
{
    mat4 perspective = {
        { 1.0f/(aspect*tan(fov/2.0f)), 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f/tan(fov/2.0f), 0.0f, 0.0f },
        { 0.0f, 0.0f, -((far+near)/(far-near)), -((2*far*near)/(far-near)) },
        { 0.0f, 0.0f, -1.0f, 0.0f }
    };

    memcpy(dest, perspective, sizeof(mat4));
}

void mat4_lookat(mat4 dest, vec3 eye, vec3 target, vec3 up)
{
    vec3 target_cpy = {0};
    memcpy(target_cpy, target, sizeof(vec3));
    vec3_sub(target_cpy, target_cpy, eye);

    vec3 zaxis = {0};
    vec3_normalize(zaxis, target_cpy);

    vec3 zaxis_cpy = {0};
    memcpy(zaxis_cpy, zaxis, sizeof(vec3));
    vec3_cross(zaxis_cpy, zaxis, up);

    vec3 xaxis = {0};
    vec3_normalize(xaxis, zaxis_cpy);

    vec3 yaxis = {0};
    vec3_cross(yaxis, xaxis, zaxis);

    zaxis[0] = -zaxis[0];
    zaxis[1] = -zaxis[1];
    zaxis[2] = -zaxis[2];

    mat4 view = {
        { xaxis[0], xaxis[1], xaxis[2], -vec3_dot(xaxis, eye) },
        { yaxis[0], yaxis[1], yaxis[2], -vec3_dot(yaxis, eye) },
        { zaxis[0], zaxis[1], zaxis[2], -vec3_dot(zaxis, eye) },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    memcpy(dest, view, sizeof(mat4));
}

void vec2_sub(vec2 dest, vec2 a, vec2 b)
{
    vec2 res = {0};
    for (int i=0; i<2; i++) res[i] = a[i] - b[i];
    memcpy(dest, res, sizeof(vec2));
}

void vec3_sub(vec3 dest, vec3 a, vec3 b)
{
    vec3 res = {0};
    for (int i=0; i<3; i++) res[i] = a[i] - b[i];
    memcpy(dest, res, sizeof(vec3));
}

void vec4_sub(vec4 dest, vec4 a, vec4 b)
{
    vec4 res = {0};
    for (int i=0; i<4; i++) res[i] = a[i] - b[i];
    memcpy(dest, res, sizeof(vec4));
}

void vec2_add(vec2 dest, vec2 a, vec2 b)
{
    vec2 res = {0};
    for (int i=0; i<2; i++) res[i] = a[i] + b[i];
    memcpy(dest, res, sizeof(vec2));
}

void vec3_add(vec3 dest, vec3 a, vec3 b)
{
    vec3 res = {0};
    for (int i=0; i<3; i++) res[i] = a[i] + b[i];
    memcpy(dest, res, sizeof(vec3));
}

void vec4_add(vec4 dest, vec4 a, vec4 b)
{
    vec4 res = {0};
    for (int i=0; i<4; i++) res[i] = a[i] + b[i];
    memcpy(dest, res, sizeof(vec4));
}

void vec2_normalize(vec2 dest, vec2 a)
{
    vec2 res = {0};
    memcpy(res, a, sizeof(vec2));
    float w = sqrt(a[0] * a[0] + a[1] * a[1]);
    res[0] /= w;
    res[1] /= w;
    memcpy(dest, res, sizeof(vec2));
}

void vec3_normalize(vec3 dest, vec3 a)
{
    vec3 res = {0};
    memcpy(res, a, sizeof(vec3));
    float w = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    res[0] /= w;
    res[1] /= w;
    res[2] /= w;
    memcpy(dest, res, sizeof(vec3));
}

void vec4_normalize(vec4 dest, vec4 a)
{
    vec4 res = {0};
    memcpy(res, a, sizeof(vec4));
    float w = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    res[0] /= w;
    res[1] /= w;
    res[2] /= w;
    res[3] /= w;
    memcpy(dest, res, sizeof(vec4));
}

void vec2_scale(vec2 dest, vec2 a, float scale)
{
    memcpy(dest, a, sizeof(vec2));
    for (int i=0; i<2; i++) dest[i] *= scale;
}

void vec3_scale(vec3 dest, vec3 a, float scale)
{
    memcpy(dest, a, sizeof(vec3));
    for (int i=0; i<3; i++) dest[i] *= scale;
}

void vec4_scale(vec4 dest, vec4 a, float scale)
{
    memcpy(dest, a, sizeof(vec4));
    for (int i=0; i<4; i++) dest[i] *= scale;
}

float *check_vec3 (lua_State *L, uint32_t arg) {
    void *ud = luaL_checkudata(L, arg, "Vec3");
    luaL_argcheck(L, ud != NULL, arg, "`Vec3` expected");
    return (float *)ud;
}

int l_vec3(lua_State *L)
{
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    double z = luaL_checknumber(L, 3);

    float *v = (float *) lua_newuserdata(L, sizeof(vec3));

    luaL_getmetatable(L, "Vec3");
    lua_setmetatable(L, -2);

    v[0] = (float)x;
    v[1] = (float)y;
    v[2] = (float)z;

    return 1;
}

int l_vec3_add(lua_State *L)
{
    float *self = check_vec3(L, 1); 
    float *other = check_vec3(L, 2); 

    float *v = (float *) lua_newuserdata(L, sizeof(vec3));

    luaL_getmetatable(L, "Vec3");
    lua_setmetatable(L, -2);

    v[0] = self[0] + other[0];
    v[1] = self[1] + other[1];
    v[2] = self[2] + other[2]; 

    return 1;
}

int l_vec3_sub(lua_State *L)
{
    float *self = check_vec3(L, 1); 
    float *other = check_vec3(L, 2); 

    float *v = (float *) lua_newuserdata(L, sizeof(vec3));

    luaL_getmetatable(L, "Vec3");
    lua_setmetatable(L, -2);

    v[0] = self[0] - other[0];
    v[1] = self[1] - other[1];
    v[2] = self[2] - other[2]; 

    return 1;
}

int l_vec3_equal(lua_State *L)
{
    float *self = check_vec3(L, 1);
    float *other = check_vec3(L, 2);

    lua_pushboolean(L, self[0] == other[0] && self[1] == other[1] && self[2] == self[2]);

    return 1;
}

int l_vec3_negate(lua_State *L)
{
    float *self = check_vec3(L, 1);

    float *v = (float *) lua_newuserdata(L, sizeof(vec3));

    luaL_getmetatable(L, "Vec3");
    lua_setmetatable(L, -2);

    v[0] = -self[0];
    v[1] = -self[1];
    v[2] = -self[2]; 

    return 1;
}

int l_vec3_mul(lua_State *L)
{
    float *self = check_vec3(L, 1);


    if (lua_type(L, 2) == LUA_TUSERDATA) {
        float *other = check_vec3(L, 2);
        float result = 0.0f;
        for (int i=0; i<3; i++) {
            result += self[i] * ((float *)other)[i];
        }
        lua_pushnumber(L, result);
        return 1;
    } else {
        float n = (float) luaL_checknumber(L, 2);
        float *v = (float *) lua_newuserdata(L, sizeof(vec3));

        luaL_getmetatable(L, "Vec3");
        lua_setmetatable(L, -2);

        v[0] = self[0] * n;
        v[1] = self[1] * n;
        v[2] = self[2] * n; 

        return 1;    
    }

    return luaL_error(L, "expected `Vec3` or `number` as parameter #1"); 
}

int l_vec3_div(lua_State *L)
{
    float *self = check_vec3(L, 1); 

    float n = (float) luaL_checknumber(L, 1);

    float *v = (float *) lua_newuserdata(L, sizeof(vec3));

    luaL_getmetatable(L, "Vec3");
    lua_setmetatable(L, -2);


    v[0] = self[0] / n;
    v[1] = self[1] / n;
    v[2] = self[2] / n; 

    return 1;
}

int l_vec3_tostring(lua_State *L)
{
    float *self = check_vec3(L, 1); 
    lua_pushfstring(L, "(%f, %f, %f)", self[0], self[1], self[2]);
    return 1;
}

int l_vec3_index(lua_State *L)
{
    float *self = check_vec3(L, 1);
    const char* index = luaL_checkstring(L, 2);
    
    if (strcmp(index, "x") == 0) {
        lua_pushnumber(L, self[0]);
        return 1;
    } else if (strcmp(index, "y") == 0) {
        lua_pushnumber(L, self[1]);
        return 1;
    } else if (strcmp(index, "z") == 0) {
        lua_pushnumber(L, self[2]);
        return 1;
    }

    return luaL_error(L, "invalid member for `Vec3`");
}

int l_vec3_newindex(lua_State *L)
{
    float *self = check_vec3(L, 1);
    const char* index = luaL_checkstring(L, 2);
    float n = (float) luaL_checknumber(L, 3);
    
    if (strcmp(index, "x") == 0) {
        self[0] = n;
        return 0;
    } else if (strcmp(index, "y") == 0) {
        self[1] = n;
        return 0;
    } else if (strcmp(index, "z") == 0) {
        self[2] = n;
        return 0;
    }

    return luaL_error(L, "invalid member for `Vec3`");
}
