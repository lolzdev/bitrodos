#include <rendering/renderer.h>

render_state_t RENDER_STATE;
static float last_frame = 0.0f;

void render_loop()
{
    float current = (float) glfwGetTime();
    RENDER_STATE.delta_time = current - last_frame;
    last_frame = current;

    glUseProgram(RENDER_STATE.shader);

    uint32_t perspective_location = glGetUniformLocation(RENDER_STATE.shader, "perspective");
    uint32_t view_location = glGetUniformLocation(RENDER_STATE.shader, "view");
    glUniformMatrix4fv(perspective_location, 1, 1, RENDER_STATE.perspective[0]);
    mat4 view = {0};
    camera_view_matrix(RENDER_STATE.camera, view);
    glUniformMatrix4fv(view_location, 1, 1, view[0]);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    meshes_t *list = RENDER_STATE.meshes;

    while (list) {
        glBindVertexArray(list->mesh->vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); 
        glBindVertexArray(0);
        list = list->next;
    }

}

void create_mesh(mesh_t *mesh, float *vertices, size_t vertices_len, uint32_t *indices, size_t indices_len)
{
    if (!mesh) {
        mesh = (mesh_t *) malloc(sizeof(mesh_t));
    }

    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glGenBuffers(1, &mesh->ebo);

    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_len, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices_len, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

meshes_t *push_mesh(meshes_t *head, mesh_t mesh)
{
    if (!head) {
       head = (meshes_t *) malloc(sizeof(meshes_t)); 
       head->mesh = (mesh_t *) malloc(sizeof(mesh_t));
       memcpy(head->mesh, &mesh, sizeof(mesh_t));
    } else {
        while (head) {
            head = head->next;
        }

        head->mesh = (mesh_t *) malloc(sizeof(mesh_t));
        memcpy(head->mesh, &mesh, sizeof(mesh_t));
    }

    return head;
}

void destroy_meshes(meshes_t *head)
{
    meshes_t *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

mesh_t *get_mesh(meshes_t *head, uint32_t index)
{
    mesh_t *found = NULL;
    uint32_t i = 0;

    while (head->next != NULL && i != index) {
        head = head->next;
        i++; 
    }

    found = head->mesh;

    return found;
}

void remove_mesh(meshes_t *head, uint32_t index)
{
    meshes_t *tmp = NULL;
    meshes_t *prev = NULL;
    uint32_t i = 0;

    while (head->next != NULL && i != index) {
        prev = head;
        head = head->next;
        i++; 
    }
    
    tmp = head;
    prev->next = head->next;
    free(tmp);
}
