#pragma once
#include <glad/glad.h>
#include <vector>
class Actor
{
public:
	Actor();
	virtual void draw();
	virtual void loadVerts() = 0;
	virtual void vertexSpecify() = 0;

protected:
	std::vector<GLfloat> vertices;
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint vertCount = 0;
};

