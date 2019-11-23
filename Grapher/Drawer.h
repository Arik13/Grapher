#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>
#include "Function.h"
#include "VectorFunction.h"

struct GraphParameters {
	int width = 900;
	int height = 900;
	int axisWidth = 1;
	int lineWidth = 2;
	int pointSize = 2;
	int numHorMajorTicks = 8;
	int numVerMajorTicks = 8;
	float red = 0;
	float green = 1;
	float blue = 0;
	float majorTickLength = 0.02;
	float maxVisDomain = 5;
	float minVisDomain = -5;
	float maxVisRange = 5;
	float minVisRange = -5;
};
GLFWwindow* bootOpenGL(int width, int height);
void drawAxes(GraphParameters& gp);
void drawData(GraphParameters& gp);
void drawFunction(GraphParameters& gp, Function* function);
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
void drawVectorFunction(GraphParameters& gp, VectorFunction* function, float lo, float hi);
GLfloat* calculateVertices(char vars[], int resolution, int dim, Function* func, GraphParameters& gp);