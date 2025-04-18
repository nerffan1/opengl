#include "Triangle.h"

Triangle::Triangle() 
{
	vertices = std::vector<GLfloat>({
	-0.5f,  0.5f, 0.0f, // Top-left
	 0.5f,  0.5f, 0.0f, // Top-right
	 0.5f, -0.5f, 0.0f, // Bottom-right
	});
};


void Triangle::vertexSpecify()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
	// Vertex attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	// Unbind VAO (do not unbind EBO while VAO is bound!)
	glBindVertexArray(0);
}
