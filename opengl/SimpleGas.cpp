#include "SimpleGas.h"

    simpleGas::simpleGas(const glm::vec3& boxMin, const glm::vec3& boxMax, int numParticles) : mBoxMin(boxMin), mBoxMax(boxMax) {
        mPoints.resize(numParticles);
        std::random_device rd;  // Obtain a random seed from the OS
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<float> distX(boxMin.x, boxMax.x);
        std::uniform_real_distribution<float> distY(boxMin.y, boxMax.y);
        std::uniform_real_distribution<float> distZ(boxMin.z, boxMax.z);

        for (auto& p : mPoints) {
            p.x = distX(gen);
            p.y = distY(gen);
            p.z = distZ(gen);
        }


        vertexSpecify();
    }

    void simpleGas::draw() {
        glBindVertexArray(mVAO);
        glDrawArrays(GL_POINTS, 0, mPoints.size());
        glBindVertexArray(0);  // Good practice
    }

    void simpleGas::vertexSpecify() {
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);

        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mPoints.size() * sizeof(glm::vec3), mPoints.data(), GL_DYNAMIC_DRAW); // Dynamic for updates

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void simpleGas::update()  {
        // 1. Collision detection (brute force - you'll optimize this later!)
        for (size_t i = 0; i < mPoints.size(); ++i) {
            for (size_t j = i + 1; j < mPoints.size(); ++j) {
                // ... (Collision detection and response logic - example below)
            }
        }

        // 2. Boundary collisions (simple example – adjust for your needs)
        for (auto& p : mPoints) {
            if (p.x < mBoxMin.x) p.x = mBoxMin.x;
            if (p.x > mBoxMax.x) p.x = mBoxMax.x;
            // ... (Similar checks for y and z)
        }

        // 3. Update VBO (send new positions to GPU)
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, mPoints.size() * sizeof(glm::vec3), mPoints.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

