#include "window.h"

 GLFWwindow* initWindow()
{
    //Initial Parameters
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Set up
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learning OpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window and " << std::endl;
        glfwTerminate();
        return nullptr ;
    }

	// The context will remain current until you make another context current or 
    // until the window owning the current context is destroyed.
    glfwMakeContextCurrent(window); 
    gladLoadGL();

    // This sets the function that will be called after resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
