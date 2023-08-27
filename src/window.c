#include <window.h>

static state_t *STATE;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    UNUSED(window);
    glViewport(0, 0, width, height);

    hook_node_t *hooks = STATE->resize_hooks;
    while (hooks) {
        if (hooks->ref == LUA_NOREF) {
            hooks = hooks->next;
            continue;
        }

        lua_rawgeti(STATE->L, LUA_REGISTRYINDEX, hooks->ref);
        lua_pushinteger(STATE->L, width);
        lua_pushinteger(STATE->L, height);
        if (lua_pcall(STATE->L, 2, 0, 0) != LUA_OK) error("A lua resize hook has thrown an error: %s", lua_tostring(STATE->L, -1));
        hooks = hooks->next;
    }

}

GLFWwindow *create_window(char *title, uint64_t width, uint64_t height, state_t *state)
{
    STATE = state;
    info("Initializing the main window");
    CRITICAL_ASSERT("Could not initialize GLFW!", glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window;
    window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    CRITICAL_ASSERT("Could not create the main window!", window);

    glfwMakeContextCurrent(window);
    int version = gladLoadGL(glfwGetProcAddress);

    CRITICAL_ASSERT("Could not create OpenGL context!", version != 0);

    info("Loaded OpenGL %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glViewport(0, 0, width, height);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

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
    //process_input(window);
    glfwSwapBuffers(window);
}

void destroy_window(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
