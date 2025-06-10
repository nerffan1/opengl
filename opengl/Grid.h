#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "Entity.h"
#include "GridComp.h"


struct Cell {
	glm::vec3 topLeft;
	glm::vec3 bottomRight;
	int subDivisions = 0; // 0 means leaf node
};

class Grid : public Entity {
public:
    Grid();
    const std::vector<Cell>& getCells() const { return mCells; }

private:
    std::vector<Cell> mCells;
    std::vector<glm::vec3> mNodes;
	std::unique_ptr<GridGraphicsComponent> mGridComp;
};
