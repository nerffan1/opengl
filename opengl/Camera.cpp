#include "Camera.h"
#include "AssetManager.h"

Camera::Camera() :
	mProjection(glm::ortho(-50.0f,50.0f,-50.0f,50.0f,0.0f,1.0f)),
	mPos(glm::vec3(0.0f, 0.0f, 1.0f))
{
}

void Camera::Update(const float& dt)
{
    //Camera
    transformLoc = glGetUniformLocation(AssetManager::Instance().GetShader("simple"), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mProjection));
}
