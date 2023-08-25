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
