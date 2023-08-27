#include <mods.h>
#include <stdlib.h>
#include <window.h>
#include <rendering/renderer.h>

int main(void)
{

    GLFWwindow *window = create_window("bitrodos", 800, 600);

    state_t state = {0};

    load_mods(&state);

    hook_node_t *hooks = state.pre_init_hooks;
    while (hooks) {
        if (hooks->ref == LUA_NOREF) {
            hooks = hooks->next;
            continue;
        }

        lua_rawgeti(state.L, LUA_REGISTRYINDEX, hooks->ref);
        if (lua_pcall(state.L, 0, 0, 0) != LUA_OK) error("A lua pre-init hook has thrown an error");
        hooks = hooks->next;
    }

    //camera_t *camera = malloc(sizeof(camera_t));
    //vec3 position = {0.0f, 0.0f, 2.0f};
    //camera_create(camera, position, -90.0f, 0.0f);
    //RENDER_STATE.camera = camera;
    //mat4_perspective(RENDER_STATE.perspective, RAD(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

    mesh_t triangle;
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f 
    };

    uint32_t indices[] = {
        0, 1, 2
    };

    create_mesh(&triangle, vertices, 9, indices, 3);
    meshes_t *meshes = NULL;
    meshes = push_mesh(meshes, triangle);

    state.meshes = meshes;

    while (!should_close(window)) {
        render_loop(&state);
        update_window(window);
    }

    info("Exiting");

    //free(camera);
    destroy_meshes(meshes);
    destroy_window(window);
    return EXIT_SUCCESS;
}
