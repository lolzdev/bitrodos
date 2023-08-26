#ifndef CAMERA_H
#define CAMERA_H

#include <math/linear.h>
#include <core.h>

typedef struct camera {
    vec3 position, front, up, right;
    float yaw, pitch, speed, sensitivity;
} camera_t;

void camera_create(camera_t *dest, vec3 position, float yaw, float pitch);
void camera_update(camera_t *camera);
void camera_view_matrix(camera_t *camera, mat4 dest);
void camera_move(camera_t *camera, direction_t direction, float delta_time);
void camera_rotate(camera_t *camera, float delta_x, float delta_y);

#endif
