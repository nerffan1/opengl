#include "SimpleGas.h"

    simpleGas::simpleGas(const glm::vec3& boxMin, const glm::vec3& boxMax, float r, int numParticles) : 
        mBoxMin(boxMin),
        mBoxMax(boxMax),
        mR(r/(2*600))
    {
        mPoints.resize(numParticles);
        std::random_device rd;  // Obtain a random seed from the OS
        std::mt19937_64 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<float> distX(boxMin.x, boxMax.x);
        std::uniform_real_distribution<float> distY(boxMin.y, boxMax.y);
        std::uniform_real_distribution<float> distZ(boxMin.z, boxMax.z);
        std::uniform_real_distribution<float> vel(-.005, .005);

        //Generate Random Initial Values
        for (auto& p : mPoints)
       {
			p.pos = {distX(gen), distY(gen), distZ(gen)};
			p.vel = {vel(gen), vel(gen), vel(gen)};
        }

        //Set up the pointsize of the squares!
		glPointSize(static_cast<GLfloat>(r));
        vertexSpecify();

    }

    void simpleGas::draw() {
        glBindVertexArray(mVAO);
        glDrawArrays(GL_POINTS, 0, mPoints.size());
    }

    void simpleGas::vertexSpecify() {
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);

        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mPoints.size() * sizeof(point), mPoints.data(), GL_DYNAMIC_DRAW); // Dynamic for updates

        // Position attribute
        glVertexAttribPointer(
            0,                  // attribute location
            3,                  // size (vec3)
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            sizeof(point),      // stride (size of the whole struct)
           (void*)0  // offset to position in struct
        );

        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void simpleGas::update(float dt)  {
        // 1. Collision detection (brute force - you'll optimize this later!)
        for (size_t i = 0; i < mPoints.size(); ++i) {
            for (size_t j = i + 1; j < mPoints.size(); ++j) {
                // ... (Collision detection and response logic - example below)
                bool overlapsX = (mPoints[i].pos.x + mR > mPoints[j].pos.x - mR) && // i's right is past j's left
                    (mPoints[i].pos.x - mR < mPoints[j].pos.x + mR);  // i's left is before j's right

                bool overlapsY = (mPoints[i].pos.y + mR > mPoints[j].pos.y - mR) && // i's top is past j's bottom
                    (mPoints[i].pos.y - mR < mPoints[j].pos.y + mR);  // i's bottom is before j's top

                if (overlapsX && overlapsY)
                {
                    glm::vec3 tmp = mPoints[i].vel;
                    mPoints[i].vel = mPoints[j].vel;
                    mPoints[j].vel = tmp;
                }
            }
        }

        // 2. Boundary collisions (simple example – adjust for your needs)
        for (auto& p : mPoints) {
            if (p.pos.x < mBoxMin.x) p.vel.x *= -1;
            if (p.pos.x > mBoxMax.x) p.vel.x *= -1;
            if (p.pos.y < mBoxMin.y) p.vel.y *= -1;
            if (p.pos.y > mBoxMax.y) p.vel.y *= -1;
            if (p.pos.z < mBoxMin.z) p.vel.z *= -1;
            if (p.pos.z > mBoxMax.z) p.vel.z *= -1;
        }

        // 3. Movement
        for (size_t i = 0; i < mPoints.size(); ++i) {
            for (size_t j = i + 1; j < mPoints.size(); ++j) {
                // ... (Collision detection and response logic - example below)
				mPoints[i].pos += mPoints[i].vel * dt; // Move point i
            }
        }

        // 4. Update VBO (send new positions to GPU)
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferSubData( GL_ARRAY_BUFFER,
            0,
            mPoints.size() * sizeof(point),
            mPoints.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

