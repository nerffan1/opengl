#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1200;

GLFWwindow* initWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
