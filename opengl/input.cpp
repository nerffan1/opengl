#include "input.h"

Input Input::instance;

Input::Input()
{
}

void Input::processInputt(GLFWwindow* window)
{
    glfwPollEvents();
    for (int i = 0; i <= GLFW_KEY_LAST; i++) {
        mCurrKeys[i] = (glfwGetKey(window, i) == GLFW_PRESS);
    }
}

Input& Input::Instance()
{
    return instance;
}
