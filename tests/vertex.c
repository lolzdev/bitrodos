#include <test.h>
#include <rendering/renderer.h>

int vertex_encoding_test()
{
    uint32_t v = encode_vertex(2, 4, 7, 0, 5);
    
    TEST(((v >> 28) & 0xf) == 2)
    TEST(((v >> 24) & 0xf) == 7)
    TEST(((v >> 16) & 0xff) == 4)
    TEST(((v >> 8) & 0xff) == 0)
    TEST((v & 0xff) == 5)

    OK
}

int main(void)
{
    RUN_TEST(vertex_encoding_test);

    return 0;
}
