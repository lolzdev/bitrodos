#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include <core.h>
#include <camera.h>
#include <rendering/renderer.h>
#include <GLFW/glfw3.h>

void mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in);
void process_input(GLFWwindow *window);

#endif
