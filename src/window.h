#ifndef WINDOW_H
#define WINDOW_H

#include <glad/gl.h>
#include <core.h>
#include <GLFW/glfw3.h>
#include <log.h>

GLFWwindow *create_window(char *title, uint64_t width, uint64_t height);
void update_window(GLFWwindow *window);
void destroy_window(GLFWwindow *window);
int should_close(GLFWwindow *window);

#endif
