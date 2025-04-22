#pragma once
#include "Actor.h"
#include <vector>
#include "glad/glad.h"

class Triangle : public Actor
{
public:
    Triangle();
	void vertexSpecify() override;
	void update() override;
	
	//Movement
	void move(GLfloat x, GLfloat y, GLfloat z);
	std::vector<GLuint> color;
};

