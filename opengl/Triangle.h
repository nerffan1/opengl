#pragma once
#include "Actor.h"
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/glm.hpp>

class Triangle : public Actor
{
public:
    Triangle();
    Triangle(glm::vec3 color);
	void vertexSpecify() override;
	void update() override;
	
	//Movement
	void move(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 color;
};

