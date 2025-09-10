#include "AssetManager.h"
#include "Shader.h"

// Define the static instance and static members
AssetManager AssetManager::instance;  // ✅ defines the static instance

void AssetManager::Initiate()
{
    CreateShaders();

    //Create Box
    float width = 100.0f;
	CreateGas(width);
    CreateGrid(width);
}

void AssetManager::CreateGrid(const float& width)
{
	mEntities.push_back(std::make_unique<SquareGrid>(8,8,width,width));
	mEntities.back()->addComponent(std::make_unique<Input_Grid>());

}

void AssetManager::CreateGas(const float& width)
{
    mActors.push_back(std::make_unique<simpleGas>(
        glm::vec3(-width/2, -width/2, 0.0f),
        glm::vec3(width/2, width/2, 0.0f),
        8,
        3000));
}

void AssetManager::CreateCamera()
{
    //glm::mat4 trans = glm::mat4(1.);
    //trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    //unsigned int transformLoc = glGetUniformLocation(AssetManager::Instance().GetShader("simple"), "transform");
    //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void AssetManager::CreateShaders()
{
    mShaders["simple"] = std::make_unique<shader>("Shaders/simple.vert", "Shaders/simple.frag");
}

GLuint AssetManager::GetShader(const std::string& str)
{
	return mShaders[str]->mProgramObject;
}

void AssetManager::debug_print() const
{
	std::cout << "You have accessed the asset manager!\n" << this << "\n";
}
