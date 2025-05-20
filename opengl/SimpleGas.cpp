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
        std::uniform_real_distribution<float> vel(-.3, .3);

        //Generate Random Initial Values
        for (auto& p : mPoints)
       {
			p.pos = {distX(gen), distY(gen), 0.0f};
			p.vel = {vel(gen), vel(gen), 0.0f};
            p.a   = {0.0f, -0.2f, 0.0f};
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
                auto
                    minx_j = mPoints[j].pos.x - mR,
                    miny_j = mPoints[j].pos.y - mR,
                    maxx_j = mPoints[j].pos.x + mR,
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
                p.vel.y *= -1;  // Reflect velocity
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
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferSubData( GL_ARRAY_BUFFER,
            0,
            mPoints.size() * sizeof(point),
            mPoints.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

