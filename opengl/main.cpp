#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Actor.h"
#include "Triangle.h"
#include <vector>
#include "input.h"
#include <memory>
#include <glm/vec3.hpp>

glm::vec3 aa;
//Namespaces
using Actor_ptr = std::unique_ptr<Actor> ;
using Actor_vec = std::vector<Actor_ptr>;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void drawTriangles(std::vector<Actor_ptr> &actors);
void mainLoop(GLFWwindow* &window);
void vertexSpecify();
GLFWwindow* initWindow();

// Shader sources
const GLchar* vertexSource = R"glsl(
#version 460 core
in vec4 position;
void main()
{
	gl_Position = vec4(position);
})glsl";

const GLchar* vertexSource_w_color = R"glsl(
#version 460 core
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

out vec3 colour;

void main() {
  colour = vertex_colour;
  gl_Position = vec4(vertex_position, 1.0);
})glsl";

const char* frag_colorinput = R"glsl(
#version 460 core

in vec3 colour;
out vec4 FragColor;

void main()
{
   FragColor = vec4(colour, 1.0);
})glsl";

const char* fragmentSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// settings/globals
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1200;
float r = 0.0f;
float g = 0.0f;
float b = 0.0f;
GLuint vao = 0;
GLuint vbo = 0;
GLuint gGraphicsPipelineShaderProgram = 0;
//Lives on CPU
GLfloat vertices[] = {
	-0.5f,  0.5f, 0.0f, 1.0f, // Top-left
	 0.5f,  0.5f, 0.0f, 1.0f, // Top-right
	 0.5f, -0.5f, 0.0f, 1.0f, // Bottom-right
};

GLuint EBO, rectVAO = 0, rectVBO = 0;
GLfloat rectangle[]  {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
GLuint indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};



GLuint CompileShader(GLuint type, const std::string&  source){
    GLuint shaderobject;

    if (type == GL_VERTEX_SHADER){ 
        shaderobject = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == GL_FRAGMENT_SHADER) {
        shaderobject = glCreateShader(GL_FRAGMENT_SHADER);
    }
	const char* src = source.c_str();
	glShaderSource(shaderobject, 1, &src, nullptr);
	glCompileShader(shaderobject);

	return shaderobject;
}

GLuint createShaderProgram(const std::string& vertexshadersource,
     const std::string& fragmentshadersource) {
     GLuint programObject = glCreateProgram();

     GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexshadersource);
     GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentshadersource);

     glAttachShader(programObject, myVertexShader);
     glAttachShader(programObject, myFragmentShader);
     glLinkProgram(programObject);

     //Check linking
     int success;
     char infoLog[512];
     glGetProgramiv(programObject, GL_LINK_STATUS, &success);
     if (!success) {
         glGetProgramInfoLog(programObject, 512, NULL, infoLog);
         std::cout << infoLog;
     }

     // Validate our program
     glValidateProgram(programObject);

     //Delete and detach shader

     return programObject;
 }

void createGraphicsPipeline()
{
    gGraphicsPipelineShaderProgram = createShaderProgram(vertexSource_w_color, frag_colorinput);
}

int main()
{
    // glfw: initialize and configure GLFW. Resources are allocated.
    // Return GLFW_TRUE if successful
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = initWindow();
    createGraphicsPipeline();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // RENDER loop (MAIN LOOP)
    // This function return true only when the user closes the window (inversion?).
    mainLoop(window);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void preDraw() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(20);

    glUseProgram(gGraphicsPipelineShaderProgram);
}

void drawTriangles(std::vector<Actor_ptr> &actors)
{
    //Draw actors
    for (auto& actor : actors)
    {
        actor->update();
        actor->draw();
    }
}

void updateVertexData() {
    // Modify your vertices array here, for example:
    //vertices[4] = sin(glfwGetTime()) * 0.2f; // Move a vertex based on time

    // Update the buffer data without recreating it
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    // Alternative: glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void mainLoop(GLFWwindow* &window)
{
    //Test Triangle pointers and vector
	std::vector<Actor_ptr> actors;
	actors.push_back(std::make_unique<Triangle>());
	actors.push_back(std::make_unique<Triangle>());
	actors.push_back(std::make_unique<Triangle>());

    //Loop!
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window, actors);

        // render Commands here
        // ------
        preDraw();
        drawTriangles(actors);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}



void vertexSpecify()
{
    //  GPU Setup
    // VAOs
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao); //Create "object name" identifier
    glBindVertexArray(vao);

    //VBOs
    // Create a Vertex Buffer Object and copy the vertex data to it
    // According to Anton's OpenGL tutorials, this is 
    glGenBuffers(1, &vbo);//Allocated memory gets actually copied into bound buffer memory (initialized)
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //Allocate storage and created object, to hold vertex data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Configures currently bound buffer and gets name

    // "To associate data going into our vertex shader, which is the entrance all
    // vertex data take to get processed by OpenGL, we need to connect our shader 'in' "
    // Vertex Attribute Array
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
};


 GLFWwindow* initWindow()
{
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

