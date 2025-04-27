#include "Triangle.h"
using namespace glm;

Triangle::Triangle() 
{
	vertices = std::vector<GLfloat>({
	-0.5f,  0.5f, 0.0f, // Top-left
	 0.5f,  0.5f, 0.0f, // Top-right
	 0.5f, -0.5f, 0.0f, // Bottom-right
	});
	color = {
		vec3(1.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(0.0f, 0.0f, 1.0f)};
	vertexSpecify();
	vertCount = 3;
}
Triangle::Triangle(std::vector<vec3> colour)
{
	Triangle();
	color = colour;
} 

void Triangle::vertexSpecify()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Color Buffer
	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec3), color.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	// Unbind VAO (do not unbind EBO while VAO is bound!)
	glBindVertexArray(0);
}

void Triangle::update()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
	colorUpdate();
}

void Triangle::colorUpdate()
{
	color[0] += vec3(-.0001f, 0.0f, .0001f);
	color[1] += vec3(.0001f, -.0001f,  0.0f);
	color[2] += vec3( 0.0f, .0001f, -.0001f);

    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, color.size() * sizeof(vec3), color.data());

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

