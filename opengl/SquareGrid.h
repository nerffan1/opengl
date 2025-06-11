#pragma once
#include "Grid.h"

class squareGrid : public Grid {
public:
	squareGrid(const int x, const int y, const float width = 1.0f, const float height = 1.0f);
private:
	int xDiv, yDiv;
	float a, b;
};
