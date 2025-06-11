#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Actor.h"
#include "Triangle.h"
#include "input.h"
#include "SimpleGas.h"
#include <vector>
#include <memory>
#include <chrono>
#include "window.h"
#include "Shader.h"
#include "AssetManager.h"


glm::vec3 aa;
//Actors
using Actor_ptr = std::unique_ptr<Actor> ;
using Actor_vec = std::vector<Actor_ptr>;
//Shaders
using shader_ptr = std::unique_ptr<shader>;
using shader_vec = std::vector<shader_ptr>;
//Clock
using Clock = std::chrono::steady_clock; // Or high_resolution_clock

void drawActors(std::vector<Actor_ptr> &actors);
void mainLoop(GLFWwindow* window);
void vertexSpecify();

// settings/globals
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGH;
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

void createGraphicsPipeline(shader_vec& shaders)
{
    shaders.push_back(std::make_unique<shader>("Shaders/simple.vert", "Shaders/simple.frag"));
    gGraphicsPipelineShaderProgram = shaders[0]->mProgramObject;
}

int main()
{
    GLFWwindow* window = initWindow();

    shader_vec shaders;
    createGraphicsPipeline(shaders);

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



void preDraw() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(gGraphicsPipelineShaderProgram);
}

void drawEntities ()
{
    //Draw actors
    // HOW CAN WE EXPAND THIS TO BE MORE UNIVERSAL OF ALL TO-RENDER ITEMS?
    for (auto& actor : AssetManager::Instance().mActors)
    {
        actor->draw();
    }
    
    //Other entities
	for (auto& entity : AssetManager::Instance().mEntities)
	{
		entity->draw();
	}
}

void updateActors(std::vector<Actor_ptr>& actors, float dt)
{
    for (auto& actor : actors)
    {
        actor->update(dt);
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

void updateSystem(const float& dt)
{
	for (auto& asset : AssetManager::Instance().mEntities)
	{
		asset->update(dt); // Assuming a fixed timestep of 16ms (60 FPS)
	}

	for (auto& asset : AssetManager::Instance().mActors)
	{
		asset->update(dt); // Assuming a fixed timestep of 16ms (60 FPS)
	}
}

void mainLoop(GLFWwindow* window)
{

    //Create Assets
    AssetManager::Instance().PopulateSystem();

    auto lastT = std::chrono::steady_clock::now(); // Use steady_clock!

    // Timing constants
    constexpr float TARGET_FPS = 60.0f;
    constexpr float TARGET_DT = 1.0f / TARGET_FPS; // Fixed timestep for updates
    constexpr float MAX_FRAME_TIME = 0.1f;         // Avoid spiral of death (10 FPS min)

    // Time tracking variables
    auto previousTime = Clock::now();
    float accumulatedTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {

        // 1. Calculate Real Frame Time (dt for the rendering frame)
        auto currentTime = Clock::now();
        float frameTime = std::chrono::duration<float>(currentTime - previousTime).count();
        previousTime = currentTime;

        // 2. Clamp frame time to prevent huge jumps after pauses/debugging
        frameTime = std::min(frameTime, MAX_FRAME_TIME);

        // 3. Accumulate frame time
        accumulatedTime += frameTime;

        //4 Process Input
		processInput(window);

        // 5. Fixed Timestep Updates
        // Run update logic multiple times if necessary to catch up
        while (accumulatedTime >= TARGET_DT)
        {
			updateSystem(TARGET_DT); // Update the system with fixed timestep
            accumulatedTime -= TARGET_DT;
        }

        // render Commands here
        preDraw();
        drawEntities();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
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



