#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        b = fminf(b + 0.0005f, 1.0f); // Increase color, clamp to 1.0

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        b = fmaxf(b - 0.0005f, 0.0f); // Decrease color, clamp to 0.0

    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
        g = fminf(g + 0.0005f, 1.0f); // Increase color, clamp to 1.0

    if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS)
        g = fmaxf(g - 0.0005f, 0.0f); // Decrease color, clamp to 0.0

    if (glfwGetKey(window, GLFW_KEY_INSERT) == GLFW_PRESS)
        r = fminf(r + 0.0005f, 1.0f); // Increase color, clamp to 1.0

    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
        r = fmaxf(r - 0.0005f, 0.0f); // Decrease color, clamp to 0.0

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        vertices[0] += .001;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        vertices[0] -= .001;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        vertices[1] += .001;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        vertices[1] -= .001;
}
