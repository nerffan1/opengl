#include "Triangle.h"

Triangle::Triangle() 
{
	vertices = std::vector<GLfloat>({
	-0.5f,  0.5f, 0.0f, // Top-left
	 0.5f,  0.5f, 0.0f, // Top-right
	 0.5f, -0.5f, 0.0f, // Bottom-right
	});
	vertexSpecify();
	vertCount = 3;
};


void Triangle::vertexSpecify()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);
	// Vertex attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Unbind VAO (do not unbind EBO while VAO is bound!)
	glBindVertexArray(0);
}

void Triangle::update()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
}

void Triangle::move(GLfloat x, GLfloat y, GLfloat z = 0.0f)
{
	vertices[0] += x;
	vertices[1] += y;
	vertices[2] += z;

	vertices[3] += x;
	vertices[4] += y;
	vertices[5] += z;

	vertices[6] += x;
	vertices[7] += y;
	vertices[8] += z;
}

