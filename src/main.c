#include <stdio.h>
#include "window.h"

int main(void)
{
    GLFWwindow *window = create_window("bitrodos", 800, 600);

    while (!should_close(window)) {
        update_window(window);
    }

    info("Exiting");

    destroy_window(window);
    return EXIT_SUCCESS;
}
