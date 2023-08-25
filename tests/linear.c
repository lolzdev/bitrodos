#include <math/linear.h>
#include <test.h>

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

int main(void)
{
    RUN_TEST(vec2_dot_test);
    RUN_TEST(vec3_dot_test);
    RUN_TEST(vec4_dot_test);
    RUN_TEST(vec3_cross_test);

    return 0;
}
