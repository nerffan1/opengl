#include "SquareGrid.h"

SquareGrid::SquareGrid(const int x, const int y, const float a, const float b)
	: xDiv(x), yDiv(y), a(a), b(b), mOrigin(-1.0f, -1.0f, 0.0f)
{
    mGridComp = std::make_unique<GridGraphicsComponent>();
    generateGridData();
    mGridComp->initialize();
    mGridComp->setupGrid(mNodes, mIndices);
}

void SquareGrid::generateGridData() {
    // Clear existing data
    mNodes.clear();
    mIndices.clear();

    // Reserve space for efficiency
    mNodes.reserve((xDiv + 1) * (yDiv + 1));
    mIndices.reserve(2 * (xDiv * (yDiv + 1) + yDiv * (xDiv + 1)));

    float x_stride = a / xDiv;
    float y_stride = b / yDiv;

    // Generate grid vertices
    for (int j = yDiv; j >= 0; --j) {  // Top to bottom (yDiv down to 0)
        for (int i = 0; i <= xDiv; ++i) {  // Left to right (0 to xDiv)
            glm::vec3 node(i * x_stride, j * y_stride, 0.0f);
            mNodes.emplace_back(node);
        }
    }

    // Generate indices for horizontal lines (full width lines using only endpoints)
    for (int row = 0; row <= yDiv; ++row) {
        int leftmost = row * (xDiv + 1);          // First node in row
        int rightmost = row * (xDiv + 1) + xDiv;  // Last node in row
        mIndices.push_back(leftmost);
        mIndices.push_back(rightmost);
    }

    // Generate indices for vertical lines (full height lines using only endpoints)
    for (int col = 0; col <= xDiv; ++col) {
        int topmost = col;                               // Top node in column (row 0)
        int bottommost = yDiv * (xDiv + 1) + col;       // Bottom node in column (row yDiv)
        mIndices.push_back(topmost);
        mIndices.push_back(bottommost);
    }

 }

void SquareGrid::draw() const {
    mGridComp->draw();
}

void SquareGrid::switchVisibility() {
    mGridComp->switchVisibility();
}