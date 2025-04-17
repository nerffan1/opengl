#pragma once
#include <glad/glad.h>
class Actor
{
public:
	Actor();
	virtual void draw();
	virtual void loadVerts();

protected:
	GLfloat* vertices;
	GLuint vao;
	GLuint vbo;
};

