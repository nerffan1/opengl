#pragma once
#include "Actor.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <random>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

struct point
{
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 a;
	glm::vec3 color;
};

class simpleGas : public Actor
{
public:
	simpleGas(const glm::vec3& boxMin, const glm::vec3& boxMax, float r, int numParticles = 1000);
	void draw() override;
	void vertexSpecify() override;
	void update(const float& dt) override;
	void move(GLfloat x, GLfloat y, GLfloat z = 0.0f) {};
	void updateColors();

private:
    glm::vec3 mBoxMin, mBoxMax;
    std::vector<point> mPoints;
    GLuint mVAO, mVBO; // Vertex Array Object and Vertex Buffer Object IDs
	float mR = 1;
};
