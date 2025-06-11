#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using Actor_ptr = std::unique_ptr<Actor> ;
using Actor_vec = std::vector<Actor_ptr>;

extern float r;
extern float g;
extern float b;
size_t actor_i = 1;

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    glfwPollEvents();
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
}
