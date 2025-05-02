#pragma once
#include "Actor.h"
#include "glm/glm.hpp"
#include <vector>

using namespace glm;

class simpleGas : public Actor
{
public:
	simpleGas();
	void draw() override;
	void vertexSpecify() override;
	void update() override;

private:
	std::vector<vec3> mPoints;
};
