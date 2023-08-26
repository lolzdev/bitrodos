#ifndef CAMERA_H
#define CAMERA_H

#include <math/linear.h>

typedef struct camera {
    vec3 position, front, up, right;
    float yaw, pitch, speed, sensitivity;
} camera_t;

void camera_create(camera_t *dest, vec3 position, float yaw, float pitch);
void camera_update(camera_t *camera);
void camera_view_matrix(camera_t *camera, mat4 dest);

#endif
