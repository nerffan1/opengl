#include "Grid.h"
#include "GridComp.h"

Grid::Grid():
	mGridComp(std::make_unique<GridGraphicsComponent>())
{
}

void Grid::update(float& dt)
{
	mGridComp->update(dt);
}
