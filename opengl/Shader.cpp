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
    GLuint shaderobject;

    if (type == GL_VERTEX_SHADER) {
        shaderobject = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == GL_FRAGMENT_SHADER) {
        shaderobject = glCreateShader(GL_FRAGMENT_SHADER);
    }
    const char* src = source.c_str();
    glShaderSource(shaderobject, 1, &src, nullptr);
    glCompileShader(shaderobject);

    return shaderobject;
};


std::string shader::LoadShaderAsString(const std::string &filename) {
    // Resulting shader program loaded as a single string
    std::string result = "";

    std::string line = "";
    std::ifstream myFile(filename.c_str());

    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            result += line + '\n';
        }
        myFile.close();
    }

    return result;
}

