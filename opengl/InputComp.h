#pragma once
#include "input.h"
#include "Component.h"

class InputComp : public Component
{
    // Core lifecycle methods
    virtual void initialize() = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void destroy() = 0;
};

class Input_Grid : public InputComp
{
public:
    Input_Grid() = default;
    void initialize() override {}
    void update(const float& deltaTime) override {
        // Use the Input singleton to check if ESC is pressed
        if (Input::Instance().getCurrKeys()[GLFW_KEY_ESCAPE]) {
            Input::Instance().CloseWindow();
        }
        // Color adjustment step
        constexpr float colorStep = 0.05f;

        // PAGE_UP: Increase blue
        if (Input::Instance().getCurrKeys()[GLFW_KEY_PAGE_UP]) {
            b = std::min(b + colorStep, 1.0f);
        }
        // PAGE_DOWN: Decrease blue
        if (Input::Instance().getCurrKeys()[GLFW_KEY_PAGE_DOWN]) {
            b = std::max(b - colorStep, 0.0f);
        }
        // HOME: Increase green
        if (Input::Instance().getCurrKeys()[GLFW_KEY_HOME]) {
            g = std::min(g + colorStep, 1.0f);
        }
        // END: Decrease green
        if (Input::Instance().getCurrKeys()[GLFW_KEY_END]) {
            g = std::max(g - colorStep, 0.0f);
        }
        // INSERT: Increase red
        if (Input::Instance().getCurrKeys()[GLFW_KEY_INSERT]) {
            r = std::min(r + colorStep, 1.0f);
        }
        // DELETE: Decrease red
        if (Input::Instance().getCurrKeys()[GLFW_KEY_DELETE]) {
            r = std::max(r - colorStep, 0.0f);
        }
    }
    void destroy() override {}
};

