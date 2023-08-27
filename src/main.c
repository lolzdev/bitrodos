#include <mods.h>
#include <stdlib.h>
#include <window.h>
#include <rendering/renderer.h>

int main(void)
{
    state_t state = {0};

    state.resize_hooks = (hook_node_t *) malloc(sizeof(hook_node_t)); 
    state.resize_hooks->ref = LUA_NOREF;

    GLFWwindow *window = create_window("bitrodos", 800, 600, &state);

    load_mods(&state);

    hook_node_t *hooks = state.pre_init_hooks;
    while (hooks) {
        if (hooks->ref == LUA_NOREF) {
            hooks = hooks->next;
            continue;
        }

        lua_rawgeti(state.L, LUA_REGISTRYINDEX, hooks->ref);
        if (lua_pcall(state.L, 0, 0, 0) != LUA_OK) error("A lua pre-init hook has thrown an error: %s", lua_tostring(state.L, -1));
        hooks = hooks->next;
    }

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

    init_input(&state);

    while (!should_close(window)) {
        hooks = state.tick_hooks;
        while (hooks) {
            if (hooks->ref == LUA_NOREF) {
                hooks = hooks->next;
                continue;
            }

            lua_rawgeti(state.L, LUA_REGISTRYINDEX, hooks->ref);
            lua_pushnumber(state.L, state.delta_time);
            if (lua_pcall(state.L, 1, 0, 0) != LUA_OK) error("A lua tick hook has thrown an error: %s", lua_tostring(state.L, -1));
            hooks = hooks->next;
        }

        render_loop(&state);
        update_window(window);
    }

    info("Exiting");

    destroy_meshes(meshes);
    destroy_window(window);
    return EXIT_SUCCESS;
}
