#include "linear.h"

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

int vec2_dot_test()
{
    vec2 a = {1.0f, 3.0f};
    vec2 b = {2.0f, 6.0f};
    TEST(vec2_dot(a, b) == 20)
    OK
}

int vec3_dot_test()
{
    vec3 a = {1.0f, 3.0f, 5.0f};
    vec3 b = {2.0f, 6.0f, 3.0f};
    TEST(vec3_dot(a, b) == 35)
    OK
}

int vec4_dot_test()
{
    vec4 a = {1.0f, 3.0f, 5.0f, 6.0f};
    vec4 b = {2.0f, 6.0f, 7.0f, 6.0f};
    TEST(vec4_dot(a, b) == 91)
    OK
}

int vec3_cross_test()
{
    vec3 a = {1.0f, 3.0f, 5.0f};
    vec3 b = {2.0f, 6.0f, 7.0f};
    vec3_cross(a, a, b);
    TEST(a[0] == -9)
    TEST(a[1] == 3)
    TEST(a[2] == 0)
    OK
}

