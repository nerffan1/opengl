#include "AssetManager.h"

// Define the static instance and static members
AssetManager AssetManager::instance;  // ✅ defines the static instance

void AssetManager::PopulateSystem()
{
    CreateGrid();
	CreateGas();
}

void AssetManager::CreateGrid()
{
	mEntities.push_back(std::make_unique<SquareGrid>(8,8,2.0f,2.0f));
}

void AssetManager::CreateGas()
{
    mActors.push_back(std::make_unique<simpleGas>(
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        8,
        2500));
}
