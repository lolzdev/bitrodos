#ifndef WINDOW_H
#define WINDOW_H

#include <glad/gl.h>
#include <core.h>
#include <GLFW/glfw3.h>
#include <log.h>
#include <rendering/renderer.h>
#include <math/linear.h>
#include <input.h>

GLFWwindow *create_window(char *title, uint64_t width, uint64_t height, state_t *state);
void update_window(GLFWwindow *window);
void destroy_window(GLFWwindow *window);
int should_close(GLFWwindow *window);

#endif
