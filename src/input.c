#include <input.h>

static float last_x = 800.0f/2.0f;
static float last_y = 600.0f/2.0f;
static uint32_t first_mouse = 1;

void mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in)
{
    UNUSED(window);

    float x_pos = (float) x_pos_in;
    float y_pos = (float) y_pos_in;

    if (first_mouse)
    {
        last_x = x_pos;
        last_y = y_pos;
        first_mouse = 0;
    }

    float x_offset = x_pos - last_x;
    float y_offset = last_y - y_pos;

    last_x = x_pos;
    last_y = y_pos;

    camera_rotate(RENDER_STATE.camera, x_offset, y_offset);
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_move(RENDER_STATE.camera, NORTH, RENDER_STATE.delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_move(RENDER_STATE.camera, SOUTH, RENDER_STATE.delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_move(RENDER_STATE.camera, WEST, RENDER_STATE.delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_move(RENDER_STATE.camera, EAST, RENDER_STATE.delta_time);
}
