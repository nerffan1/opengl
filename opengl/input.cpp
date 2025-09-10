#include "input.h"

void Input::processInputt()
{
    glfwPollEvents();
    for (int i = 0; i <= GLFW_KEY_LAST; i++) {
        mCurrKeys[i] = (glfwGetKey(mWindow, i) == GLFW_PRESS);
    }
}

Input& Input::Instance()
{
    static Input instance; // function-local static: initialized on first use
    return instance;
}
