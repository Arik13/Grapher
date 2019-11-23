#include "VAO.h"
#include <cstddef>
#include <iostream>

VAO::VAO(GLfloat* vertices, GLfloat* colors, GLushort* indices, size_t vBytes, size_t cBytes, size_t iBytes) {
	// Init VAO
	glGenVertexArrays(1, &VAOID);
	glBindVertexArray(VAOID);
	glEnableVertexAttribArray(0);	// Enable vertex attribute
	glEnableVertexAttribArray(1);	// Enable color attribute

	// Vertex buffer
	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vBytes, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Color buffer
	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, cBytes, colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	// Index buffer
	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iBytes, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &VAOID);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &indexVBO);
}

GLuint VAO::ID() {
	return VAOID;
}
