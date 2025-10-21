#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

extern float r;
extern float g;
extern float b;

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
