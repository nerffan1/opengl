#pragma once
#include "input.h"
#include "Component.h"

class InputComp : public Component
{
    // Core lifecycle methods
    virtual void initialize() const = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void destroy() = 0;
};

class Input_Grid : public InputComp
{
public:
    void initialize() const override {}
    void update(const float& deltaTime) override {
        // Use the Input singleton to check if ESC is pressed
        if (Input::Instance().getCurrKeys()[GLFW_KEY_ESCAPE]) {
            Input::Instance().CloseWindow();
        }
    }
    void destroy() override {}
};

