#pragma once
#include "Component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

class GridGraphicsComponent : public Component {
public:
    GridGraphicsComponent() = default;
    ~GridGraphicsComponent() = default;

    void initialize() override;
    void update(const float& deltaTime) override {}
    void destroy() override;

    void setupGrid(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices);
    void draw();
    void switchVisibility();

private:
    GLuint mVAO = 0;
    GLuint mVBO = 0;
    GLuint mEBO = 0;
    GLsizei mIndexCount = 0;
    bool mInitialized = false;
    bool mIsVisible = true;
};

// GridGraphicsComponent.cpp
