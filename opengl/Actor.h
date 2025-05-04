#pragma once
#include <glad/glad.h>
#include <vector>
class Actor
{
public:
	Actor();
	virtual void draw();
	virtual void vertexSpecify() = 0;
	virtual void update(float dt) = 0;
	virtual void move(GLfloat x, GLfloat y, GLfloat z = 0.0f) = 0;

protected:
	std::vector<GLfloat> vertices;
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint color_vbo = 0;
	GLuint vertCount = 0;
};

