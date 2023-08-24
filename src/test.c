#include "log.h"
#include "math/linear.h"
#include "window.h"
#include "test.h"


int main(void)
{
    
    RUN_TEST(vec2_dot_test)
    RUN_TEST(vec3_dot_test)
    RUN_TEST(vec4_dot_test)

    RUN_TEST(vec3_cross_test)

    info("%d/%d test cases succeeded", tested - failed, tested); 
    return failed > 0 ? 1 : 0;
}
