#pragma once
#include "Component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class GraphicsComp : public Component {
public:
    // Rendering phases
    virtual void preRender() {} // For setting up render states
    virtual void render() = 0;
    virtual void postRender() {} // For cleanup

    // Visibility control
    virtual void setVisibility(bool visible) { mIsVisible = visible; }
    bool isVisible() const { return mIsVisible; }

    // Render layer management
    virtual void setRenderLayer(int layer) { mRenderLayer = layer; }
    int getRenderLayer() const { return mRenderLayer; }

protected:
    GLuint mVAO = 0;
    GLsizei mIndexCount = 0;
    bool mNeedsRebuild = true;
    bool mInitialized = false;

    bool mIsVisible = true;
    int mRenderLayer = 0;

};

