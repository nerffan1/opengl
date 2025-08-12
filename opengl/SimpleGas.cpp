#include "SimpleGas.h"

    simpleGas::simpleGas(const glm::vec3& boxMin, const glm::vec3& boxMax, float r, int numParticles) : 
        mBoxMin(boxMin),
        mBoxMax(boxMax),
        mR(r/(2*600))
    {
        std::random_device rd;  // Obtain a random seed from the OS
        std::mt19937_64 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<float> distX(boxMin.x, boxMax.x);
        std::uniform_real_distribution<float> distY(boxMin.y, boxMax.y);
        std::uniform_real_distribution<float> vel(-.1, .1);
        std::uniform_real_distribution<float> acc(-.7, .7);

        mPoints.reserve(numParticles);  // Allocates memory only

        for (size_t i = 0; i < numParticles; ++i) {
            mPoints.emplace_back(
                glm::vec3{ distX(gen), distY(gen), 0.0f },   // pos
                glm::vec3{ vel(gen), vel(gen), 0.0f },       // vel
                glm::vec3{ 0.0f, -1.1f, 0.0f }               // a
            );
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
        // VAO + VBO
        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);

        glGenBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mPoints.size() * sizeof(point), mPoints.data(), GL_DYNAMIC_DRAW);

        // pos -> location 0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(point), (void*)offsetof(point, pos));
        glEnableVertexAttribArray(0);

        // vel as color -> location 1
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(point), (void*)offsetof(point, color));
        glEnableVertexAttribArray(1);
    }

    void simpleGas::update(const float& dt)  {
        // 1. Collision detection (brute force - you'll optimize this later!)
        const float dtsqr = dt * dt;

        for (size_t i = 0; i < mPoints.size(); ++i) {
            float
                minx_i = mPoints[i].pos.x - mR,
                miny_i = mPoints[i].pos.y - mR,
                maxx_i = mPoints[i].pos.x + mR,
                maxy_i = mPoints[i].pos.y + mR;

            for (size_t j = i + 1; j < mPoints.size(); ++j) {
                const auto
                    minx_j = mPoints[j].pos.x - mR,
                    maxx_j = mPoints[j].pos.x + mR,
                    miny_j = mPoints[j].pos.y - mR,
                    maxy_j = mPoints[j].pos.y + mR;

                auto
                    left = (maxx_i > minx_j),
                    right = (minx_i < maxx_j),
                    top = (maxy_i > miny_j),
                    bottom = (miny_i < maxy_j);


                if (left && right &&
                    top && bottom)
                {
                    // Calculate overlap on each axis
                    float x_overlap = 2 * mR - glm::abs(mPoints[i].pos.x - mPoints[j].pos.x);
                    float y_overlap = 2 * mR - glm::abs(mPoints[i].pos.y - mPoints[j].pos.y);

                    // Only adjust along the axis with the smaller overlap (more natural collision)
                    if (x_overlap < y_overlap)
                    {
                        // Move along x-axis
                        if (mPoints[i].pos.x < mPoints[j].pos.x)
                        {
                            // Box i is to the left of box j
                            mPoints[i].pos.x -= x_overlap;
                        }
                        else
                        {
                            // Box i is to the right of box j
                            mPoints[i].pos.x += x_overlap;
                        }
                    }
                    else
                    {
                        // Move along y-axis
                        if (mPoints[i].pos.y < mPoints[j].pos.y)
                        {
                            // Box i is below box j
                            mPoints[i].pos.y -= y_overlap;
                        }
                        else
                        {
                            // Box i is above box j
                            mPoints[i].pos.y += y_overlap;
                        }
                    }

                    //Update velocities for elastic collisions
					std::swap(mPoints[i].vel, mPoints[j].vel); // Swap velocities
                }
            }
        }


        // 2. Boundary collisions 
        for (auto& p : mPoints) {
            // X-axis boundary collision
            if (p.pos.x < mBoxMin.x) {
                p.vel.x *= -1;  // Reflect velocity
                p.pos.x = mBoxMin.x + mR;  // Position correction: move particle inside by radius
            }
            if (p.pos.x > mBoxMax.x) {
                p.vel.x *= -1;  // Reflect velocity
                p.pos.x = mBoxMax.x - mR;  // Position correction: move particle inside by radius
            }

            // Y-axis boundary collision
            if (p.pos.y < mBoxMin.y) {
                p.vel.y *= -0.9;  // Reflect velocity
                p.pos.y = mBoxMin.y + mR;  // Position correction: move particle inside by radius
            }
            if (p.pos.y > mBoxMax.y) {
                p.vel.y *= -1;  // Reflect velocity
                p.pos.y = mBoxMax.y - mR;  // Position correction: move particle inside by radius
            }
        }

        // 3. Movement
        for (size_t i = 0; i < mPoints.size(); ++i) {
            mPoints[i].vel += mPoints[i].a*dt; // Update velocity
			mPoints[i].pos += (mPoints[i].vel * dt) + (mPoints[i].a * 0.5f *dtsqr); // Move point i
        }

        // 4. Update VBO (send new positions to GPU)
        // During update
        updateColors();
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, mPoints.size() * sizeof(point), mPoints.data());
    }

/**
 * 
*/
    void simpleGas::updateColors() {
        // Maximum velocity intensity (sum of absolute velocities) - adjust as needed
        float maxVelocityIntensity = 1.0f;  // Set this to your desired maximum

        for (auto& p : mPoints) {
            // Calculate velocity intensity as sum of absolute velocities
            float velocityIntensity = std::abs(p.vel.x) + std::abs(p.vel.y);

            // Normalize to [0, 1] range
            float t = std::min(velocityIntensity / maxVelocityIntensity, 1.0f);

            // Apply smoothstep for smooth transitions
            t = t * t * (3.0f - 2.0f * t);

            // Color transitions: Green -> Yellow -> Orange -> Red
            if (t < 0.333f) {
                // Green to Yellow (0.0 to 0.333)
                float localT = t * 3.0f;  // Map [0, 0.333] to [0, 1]
                p.color = glm::vec3(localT, 1.0f, 0.0f);
            }
            else if (t < 0.667f) {
                // Yellow to Orange (0.333 to 0.667)
                float localT = (t - 0.333f) * 3.0f;  // Map [0.333, 0.667] to [0, 1]
                p.color = glm::vec3(1.0f, 1.0f - 0.5f * localT, 0.0f);  // Yellow (1,1,0) to Orange (1,0.5,0)
            }
            else {
                // Orange to Red (0.667 to 1.0)
                float localT = (t - 0.667f) * 3.0f;  // Map [0.667, 1] to [0, 1]
                p.color = glm::vec3(1.0f, 0.5f - 0.5f * localT, 0.0f);  // Orange (1,0.5,0) to Red (1,0,0)
            }
        }
    }

