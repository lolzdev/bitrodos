#include "window.h"

GLFWwindow *create_window(char *title, uint64_t width, uint64_t height)
{
    info("Initializing the main window");
    CRITICAL_ASSERT("Could not initialize GLFW!", glfwInit());
    GLFWwindow *window;
    window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);

    CRITICAL_ASSERT("Could not create the main window!", window);

    glfwMakeContextCurrent(window);
    info("Window initialized");

    return window;
}

int should_close(GLFWwindow *window)
{
    return glfwWindowShouldClose(window);
}

void update_window(GLFWwindow *window)
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void destroy_window(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
