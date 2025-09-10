#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

extern float r;
extern float g;
extern float b;


//void processInput(GLFWwindow* window)
//{
//    glfwPollEvents();
//
//    //Check actors that have the module
//
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
//        b = fminf(b + 0.0005f, 1.0f); // Increase color, clamp to 1.0
//
//    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
//        b = fmaxf(b - 0.0005f, 0.0f); // Decrease color, clamp to 0.0
//
//    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
//        g = fminf(g + 0.0005f, 1.0f); // Increase color, clamp to 1.0
//
//    if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS)
//        g = fmaxf(g - 0.0005f, 0.0f); // Decrease color, clamp to 0.0
//
//    if (glfwGetKey(window, GLFW_KEY_INSERT) == GLFW_PRESS)
//        r = fminf(r + 0.0005f, 1.0f); // Increase color, clamp to 1.0
//
//    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
//        r = fmaxf(r - 0.0005f, 0.0f); // Decrease color, clamp to 0.0
//}


class Input
{
public:
	static Input& Instance();
	void processInputt();
	const bool* getCurrKeys() const { return mCurrKeys; }
	const bool* getPrevKeys() const { return mPrevKeys; }

	// Window
	void CloseWindow() const { glfwSetWindowShouldClose(mWindow, true);};
	void SetWindow(GLFWwindow* window) { mWindow = window;}

private:
	// removed: static Input instance; use function-local static in Instance()
	//Decision of arrays thanks to Qwen3 Coder
	bool mCurrKeys[GLFW_KEY_LAST + 1];
	bool mPrevKeys[GLFW_KEY_LAST + 1];
	GLFWwindow* mWindow = nullptr;
};
