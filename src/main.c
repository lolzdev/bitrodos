#include <stdio.h>
#include <stdlib.h>
#include <window.h>
#include <rendering/renderer.h>
#include <assets.h>

int main(void)
{
    GLFWwindow *window = create_window("bitrodos", 800, 600);


    camera_t *camera = malloc(sizeof(camera_t));
    vec3 position = {0.0f, 0.0f, 2.0f};
    camera_create(camera, position, -90.0f, 0.0f);
    RENDER_STATE.camera = camera;
    mat4_perspective(RENDER_STATE.perspective, RAD(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

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

    uint32_t shader = load_shader_program("main.vert", "main.frag");
    RENDER_STATE.shader = shader;
    info("Shader loaded");
    RENDER_STATE.meshes = meshes;

    while (!should_close(window)) {
        render_loop();
        update_window(window);
    }

    info("Exiting");

    free(camera);
    destroy_meshes(meshes);
    destroy_window(window);
    return EXIT_SUCCESS;
}
