#pragma once
#include <glad/glad.h>
#include <vector>
#include "Component.h"
#include "Entity.h"

class Actor : public Entity
{
public:
	Actor();
	virtual void vertexSpecify() = 0;
	virtual void move(GLfloat x, GLfloat y, GLfloat z = 0.0f) = 0;
	virtual void draw() const = 0;

protected:
	std::vector<GLfloat> vertices;
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint color_vbo = 0;
	GLuint vertCount = 0;
};

