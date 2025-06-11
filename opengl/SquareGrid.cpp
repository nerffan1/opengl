#include "SquareGrid.h"

squareGrid::squareGrid(const int x, const int y, const float a, const float b):
	xDiv(x), 
	yDiv(y), 
	a(a),
	b(b)
{
	mNodes.reserve(xDiv * yDiv);
	float x_stride(a / xDiv);
	float y_stride(b / xDiv);
	for (int j = yDiv; j > 0; --j) {
		for (int i = 1; i <= xDiv; ++i) {
			glm::vec3 node(i * x_stride, j * y_stride, 0.0f);
			mNodes.emplace_back(node);
		}
	}
}
