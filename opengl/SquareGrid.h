#pragma once
#include "Grid.h"

class SquareGrid: public Grid {
public:
    SquareGrid(const int x, const int y, const float a, const float b);
    ~SquareGrid() = default;

    void draw() const;
    void switchVisibility();

private:
    void generateGridData();

    int xDiv;
    int yDiv;
    float a, b;
    glm::vec3 mOrigin;

    std::vector<glm::vec3> mNodes;
    std::vector<GLuint> mIndices;
    std::unique_ptr<GridGraphicsComponent> mGridComp;

    //Logic
    bool mUpdate = false;
};

