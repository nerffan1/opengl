#include "Grid.h"
#include "GridComp.h"

Grid::Grid():
	mGridComp(std::make_unique<GridGraphicsComponent>())
{
}

void Grid::update(const float& dt)
{
	mGridComp->update(dt);
	for (auto& comp : mComponents) {
		comp->update(dt);
	}
}
