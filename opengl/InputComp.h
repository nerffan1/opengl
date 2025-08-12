#pragma once
#include "Component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InputComp : public Component
{
    // Core lifecycle methods
    void initialize() override;
    void update(const float& deltaTime) override;
    void destroy() override;
};
