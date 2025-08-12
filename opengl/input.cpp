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
        if (mCurrKeys[i]) {
            // Key is pressed, handle the event
			std::cout << "Key " << i << " is pressed.\n";
		}
    }
}

Input& Input::Instance()
{
    return instance;
}
