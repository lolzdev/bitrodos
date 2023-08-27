#include <camera.h>

void camera_create(camera_t *dest, vec3 position, float yaw, float pitch)
{
    if (!dest) dest = (camera_t *) malloc(sizeof(camera_t));
    
    vec3 front = {0.0f, 0.0f, -1.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3 right = {0};

    camera_t camera = {0};
    memcpy(camera.position, position, sizeof(vec3));
    memcpy(camera.front, front, sizeof(vec3));
    memcpy(camera.up, up, sizeof(vec3));
    memcpy(camera.right, right, sizeof(vec3));
    camera.yaw = yaw;
    camera.pitch = pitch;
    camera.speed = 2.5f;
    camera.sensitivity = 0.1f;

    camera_update(&camera);

    memcpy(dest, &camera, sizeof(camera_t));
}

void camera_update(camera_t *camera)
{
    camera->front[0] = cos(RAD(camera->yaw)) * cos(RAD(camera->pitch));
    camera->front[1] = sin(RAD(camera->pitch));
    camera->front[2] = sin(RAD(camera->yaw)) * cos(RAD(camera->pitch));
    vec3_normalize(camera->front, camera->front);

    vec3 up = {0.0f, 1.0f, 0.0f};

    vec3_cross(camera->right, camera->front, up);
    vec3_normalize(camera->right, camera->right);

    vec3_cross(camera->up, camera->right, camera->front);
    vec3_normalize(camera->up, camera->up);
}

void camera_resize(camera_t *camera, uint32_t width, uint32_t heigth)
{
    camera->width = width;
    camera->heigth = heigth;
}

void camera_matrix(camera_t *camera, mat4 view, mat4 perspective)
{
    vec3 pos = {0};
    vec3_add(pos, camera->position, camera->front);
    mat4_lookat(view, camera->position, pos, camera->up);

    mat4_perspective(perspective, RAD(45.0f), (float)camera->width/(float)camera->heigth, 0.1f, 100.0f);
}

void camera_move(camera_t *camera, direction_t direction, float delta_time)
{
    float velocity = camera->speed * delta_time;
    vec3 res = {0};
    switch (direction) {
        case NORTH:
            vec3_scale(res, camera->front, velocity);
            vec3_add(camera->position, camera->position, res);
            break;
        case SOUTH:
            vec3_scale(res, camera->front, velocity);
            vec3_sub(camera->position, camera->position, res);
            break;
        case WEST:
            vec3_scale(res, camera->right, velocity);
            vec3_sub(camera->position, camera->position, res);
            break;
        case EAST:
            vec3_scale(res, camera->right, velocity);
            vec3_add(camera->position, camera->position, res);
            break;
        case TOP:
            vec3_scale(res, camera->up, velocity);
            vec3_add(camera->position, camera->position, res);
            break;
        case BOTTOM:
            vec3_scale(res, camera->up, velocity);
            vec3_sub(camera->position, camera->position, res);
            break;
    };
}

void camera_rotate(camera_t *camera, float delta_x, float delta_y)
{
    delta_x *= camera->sensitivity; 
    delta_y *= camera->sensitivity; 

    camera->yaw += delta_x;
    camera->pitch += delta_y;

    if (camera->pitch > 89.0f) camera->pitch = 89.0f;
    if (camera->pitch < -89.0f) camera->pitch = -89.0f;

    camera_update(camera);
}

void camera_use(camera_t *camera, uint32_t shader)
{
    uint32_t perspective_location = glGetUniformLocation(shader, "perspective");
    uint32_t view_location = glGetUniformLocation(shader, "view");
    mat4 view = {0};
    mat4 perspective = {0};
    camera_matrix(camera, view, perspective);
    glUniformMatrix4fv(view_location, 1, 1, view[0]);
    glUniformMatrix4fv(perspective_location, 1, 1, perspective[0]);
}

int l_camera_create(lua_State *L)
{
   return 0; 
}
