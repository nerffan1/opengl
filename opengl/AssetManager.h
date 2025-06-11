#pragma once
#include "Entity.h"
#include "Grid.h"
#include <vector>
#include "SquareGrid.h"
#include <memory>
#include "Actor.h"
#include "SimpleGas.h"
#include <glm/glm.hpp>

class AssetManager
{
public:
    // Singleton access
    static AssetManager& Instance() {
        return instance;
    }

    // Delete copy/move constructors and assignment operators
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;

    //Populate System
    void PopulateSystem();

    static AssetManager instance;
    std::vector<std::unique_ptr<Entity>> mEntities;
	std::vector<std::unique_ptr<Actor>> mActors;

    AssetManager() = default;
    ~AssetManager() = default;

    //Components

    // Function to create a grid and return a pointer to it
    void CreateGrid();
    //Actor Methods
    void CreateGas();
};
