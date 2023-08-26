#include <window.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    UNUSED(window);
    glViewport(0, 0, width, height);
}

GLFWwindow *create_window(char *title, uint64_t width, uint64_t height)
{
    info("Initializing the main window");
    CRITICAL_ASSERT("Could not initialize GLFW!", glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    CRITICAL_ASSERT("Could not create the main window!", window);

    glfwMakeContextCurrent(window);
    int version = gladLoadGL(glfwGetProcAddress);

    CRITICAL_ASSERT("Could not create OpenGL context!", version != 0);

    info("Loaded OpenGL %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glViewport(0, 0, width, height);

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
