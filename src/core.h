#ifndef CORE_H
#define CORE_H

#define UNUSED(x) (void)(x)

typedef enum direction {
    NORTH, // -z
    SOUTH, // +z
    WEST, // -x
    EAST, // +x
    TOP, // +y
    BOTTOM, // -y
} direction_t;

#endif
