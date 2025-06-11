#pragma once
#include "Actor.h"
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>

class Triangle : public Actor
{
public:
    Triangle();
	Triangle(std::vector<glm::vec3> colour);
	void vertexSpecify() override;
	void update(const float& dt) override;
	
	//Movement
	void move(GLfloat x, GLfloat y, GLfloat z);
	std::vector<glm::vec3> color;

	//Render Udate
	void colorUpdate();
};

