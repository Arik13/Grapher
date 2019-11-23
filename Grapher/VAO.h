#pragma once
#include <GLEW/glew.h>

class VAO {
public:
	VAO(GLfloat* vertices,
		GLfloat* colors, 
		GLushort* indices, 
		size_t vBytes, 
		size_t cBytes, 
		size_t iBytes);
	~VAO();
	GLuint ID();
private:
	GLuint VAOID = 0;
	GLuint vertexVBO = 0;
	GLuint colorVBO = 0;
	GLuint indexVBO = 0;
};

