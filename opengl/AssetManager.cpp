#include "AssetManager.h"
#include "Shader.h"

// Define the static instance and static members
AssetManager AssetManager::instance;  // ✅ defines the static instance

void AssetManager::Initiate()
{
    CreateShaders();

    //Create Box
    float width = 100.0f;
	mActors.push_back(mGasFactory.Create());
	mActors.push_back(std::make_unique<Triangle>());
	mEntities.push_back(std::make_unique<SquareGrid>(8,8,width,width));
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
