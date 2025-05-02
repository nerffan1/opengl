#pragma once
#include "Actor.h"
#include "SimpleGas.h"
#include <glad/glad.h>
#include <glm/glm.hpp>   // Make sure you have GLM
#include <random>
#include <vector>

class simpleGas : public Actor
{
public:
	simpleGas(const glm::vec3& boxMin, const glm::vec3& boxMax, int numParticles = 1000);
	void draw() override;
	void vertexSpecify() override;
	void update() override;
	void move(GLfloat x, GLfloat y, GLfloat z = 0.0f) {};

private:
    glm::vec3 mBoxMin, mBoxMax;
    std::vector<glm::vec3> mPoints;
    GLuint mVAO, mVBO; // Vertex Array Object and Vertex Buffer Object IDs
};
