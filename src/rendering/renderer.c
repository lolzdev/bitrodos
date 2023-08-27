#include <rendering/renderer.h>

static float last_frame = 0.0f;

void render_loop(state_t *state)
{
    float current = (float) glfwGetTime();
    state->delta_time = current - last_frame;
    last_frame = current;

    hook_node_t *hooks = state->render_hooks;
    while (hooks) {
        if (hooks->ref == LUA_NOREF) {
            hooks = hooks->next;
            continue;
        }

        lua_rawgeti(state->L, LUA_REGISTRYINDEX, hooks->ref);
        lua_pushnumber(state->L, state->delta_time);
        if (lua_pcall(state->L, 1, 0, 0) != LUA_OK) error("A lua render hook has thrown an error: %s", lua_tostring(state->L, -1));
        hooks = hooks->next;
    }

    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    meshes_t *list = state->meshes;

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
       head->next = NULL;
       memcpy(head->mesh, &mesh, sizeof(mesh_t));
    } else {
        while (head) {
            head = head->next;
        }

        head->mesh = (mesh_t *) malloc(sizeof(mesh_t));
        head->next = NULL;
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
