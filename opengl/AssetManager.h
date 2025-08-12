#pragma once
#include "Entity.h"
#include "Camera.h"
#include "Grid.h"
#include <vector>
#include "SquareGrid.h"
#include <memory>
#include "Actor.h"
#include "Shader.h"
#include "SimpleGas.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

using shader_map = std::unordered_map<std::string, std::unique_ptr<shader>>;
using Actor_ptr = std::unique_ptr<Actor> ;
using Actor_vec = std::vector<Actor_ptr>;

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
    void Initiate();

    std::vector<std::unique_ptr<Entity>> mEntities;
	Actor_vec mActors;
    shader_map mShaders;
    Camera mCamera;

    //Components
    std::vector<std::shared_ptr<Grid>> mInputs;

    AssetManager() = default;
    ~AssetManager() = default;

    GLuint GetShader(const std::string& str);

    //Debugging
   void debug_print() const;

private:
    static AssetManager instance;


    // Grid Methods
    void CreateGrid(const float& width);
    //Actor Methods
    void CreateGas(const float& width);
    //Camera Methods
    void CreateCamera();
    //Shaders
    void CreateShaders();
};
