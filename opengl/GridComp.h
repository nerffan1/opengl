#pragma once
#include "Component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GridGraphicsComponent : public Component {
public:
    // Component overrides
    void initialize() override {
        glGenVertexArrays(1, &mVAO);
    }

    void update(float deltaTime) override { }

    void destroy() override {
        glDeleteVertexArrays(1, &mVAO);
        // ... other GL cleanup
        mInitialized = false;
    }

    // IGraphicsComponent overrides
    void draw() {
        if (!mInitialized || !mIsVisible) return;

        glBindVertexArray(mVAO);
        glDrawElements(GL_LINES, mIndexCount, GL_UNSIGNED_INT, 0);
    }

	void switchVisibility() {
		mIsVisible = !mIsVisible;
	}

private:
    GLuint mVAO = 0;
    GLsizei mIndexCount = 0;
    bool mNeedsRebuild = true;
    bool mInitialized = false;
    bool mIsVisible = false;
};
