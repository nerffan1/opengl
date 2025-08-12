#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

class AssetManager;

class Camera {
public:
	Camera();
	void Update(const float& dt);
	//void setFov(float fov) {
	//	mFov = fov;
	//	updateProjectionMatrix();
	//}
	//void setAspectRatio(float aspectRatio) {
	//	mAspectRatio = aspectRatio;
	//	updateProjectionMatrix();
	//}
	//const glm::mat4& getProjectionMatrix() const {
	//	return mProjectionMatrix;
	//}
private:
	glm::mat4 mProjection;
	glm::vec3 mPos;
	unsigned int transformLoc;
};
