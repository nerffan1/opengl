#include "Shader.h"

shader::shader(const std::string& vertFile, const std::string& fragFile) :
	mFile(vertFile)
{
    std::string vertex_src = LoadShaderAsString(vertFile);
    std::string fragment_src = LoadShaderAsString(fragFile);
    GLuint progObj = glCreateProgram();

    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertex_src);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragment_src);

    glAttachShader(progObj, myVertexShader);
    glAttachShader(progObj, myFragmentShader);
    glLinkProgram(progObj);

    //Check linking
    int success;
    char infoLog[512];
    glGetProgramiv(progObj, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(progObj, 512, NULL, infoLog);
        std::cout << infoLog;
    }

    // Validate our program
    glValidateProgram(progObj);

    //Initialize
    mProgramObject = progObj;
};

GLuint shader::CompileShader(GLuint type, const std::string& source)
{
    GLuint shaderobject = glCreateShader(type); //OpenGL validates

    const char* src = source.c_str();
    glShaderSource(shaderobject, 1, &src, nullptr);
    glCompileShader(shaderobject);

    return shaderobject;
};


std::string shader::LoadShaderAsString(const std::string& filename) {
    // Open file at the end to get size
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Get file size
    const auto fileSize = file.tellg();
    if (fileSize == -1) {
        throw std::runtime_error("Failed to determine file size: " + filename);
    }

    // Create buffer and read file
    std::string buffer;
    buffer.resize(fileSize);  // Allocate space

    file.seekg(0);  // Rewind to start
    file.read(&buffer[0], fileSize);  // Read directly into string's memory

    // Remove all '\r' characters (Windows to Unix conversion)
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\r'), buffer.end());

    return buffer;
}
