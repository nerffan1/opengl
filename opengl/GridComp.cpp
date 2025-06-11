#include "GridComp.h"

void GridGraphicsComponent::initialize() {
    if (mInitialized) return;

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    mInitialized = true;
}

void GridGraphicsComponent::setupGrid(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices) {
    if (!mInitialized) return;

    mIndexCount = static_cast<GLsizei>(indices.size());

    glBindVertexArray(mVAO);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void GridGraphicsComponent::draw() {
    if (!mInitialized || !mIsVisible || mIndexCount == 0) return;

    glBindVertexArray(mVAO);
    glDrawElements(GL_LINES, mIndexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GridGraphicsComponent::switchVisibility() {
    mIsVisible = !mIsVisible;
}

void GridGraphicsComponent::destroy() {
    if (mInitialized) {
        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mVBO);
        glDeleteBuffers(1, &mEBO);
        mVAO = mVBO = mEBO = 0;
        mInitialized = false;
    }
}
