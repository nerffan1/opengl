#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>

class shader
{
public:
	shader(const std::string &vertexShader, const std::string &fragShader);
	GLuint mProgramObject;
protected:
	GLuint CompileShader(GLuint type, const std::string& source);
	std::string LoadShaderAsString(const std::string &filename);
	std::string mFile;
};
