#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mainLoop(GLFWwindow* &window);
void vertexSpecify();
void specifyRectangle();
GLFWwindow* initWindow();



// Shader sources
const GLchar* vertexSource = R"glsl(
#version 460 core
in vec4 position;
void main()
{
	gl_Position = vec4(position);
})glsl";

const char* fragmentSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// settings/globals
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
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
GLfloat rectangle[] = {
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
    gGraphicsPipelineShaderProgram = createShaderProgram(vertexSource, fragmentSource);
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
    //vertexSpecify();
    specifyRectangle();
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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
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

    glUseProgram(gGraphicsPipelineShaderProgram);

}

void draw() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glPointSize(20);
    glDrawArrays(GL_POINTS, 0, 3);
}

void drawRect() {
    glBindVertexArray(rectVAO);
    glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        updateVertexData();

        // render Commands here
        // ------
        preDraw();
        drawRect();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


void specifyRectangle()
{
    glGenVertexArrays(1, &rectVAO);
    glBindVertexArray(rectVAO);

    // Vertex buffer
    glGenBuffers(1, &rectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    // Element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Unbind VAO (do not unbind EBO while VAO is bound!)
    glBindVertexArray(0);
    
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


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

