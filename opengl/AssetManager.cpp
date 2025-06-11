#include "AssetManager.h"

// Define the static instance and static members
AssetManager AssetManager::instance;  // ✅ defines the static instance

void AssetManager::PopulateSystem()
{
	CreateGas();
}

void AssetManager::CreateGrid()
{
	mEntities.push_back(std::make_unique<squareGrid>(3,3));
}

void AssetManager::CreateGas()
{
    mActors.push_back(std::make_unique<simpleGas>(
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        10,
        2000));
}
