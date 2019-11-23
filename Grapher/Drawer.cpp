#include "Drawer.h"

// Draws the axes
void drawAxes(GraphParameters& gp) {
	glLineWidth(gp.axisWidth);
	glColor3f(gp.red, gp.green, gp.blue);

	// Draw Axes
	glBegin(GL_LINES);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(0, -1);
	glVertex2f(0, 1);

	// Draw Horizontal Axis
	for (int i = 1; i <= gp.numHorMajorTicks + 2; i++) {
		float horPos = -1 + 2 * ((float)i / (gp.numHorMajorTicks + 2));
		glVertex2f(horPos, 0);
		glVertex2f(horPos, gp.majorTickLength);
	}

	// Draw Vertical Axis
	for (int i = 1; i <= gp.numVerMajorTicks + 2; i++) {
		float verPos = -1 + 2 * ((float)i / (gp.numVerMajorTicks + 2));
		glVertex2f(0, verPos);
		glVertex2f(gp.majorTickLength, verPos);
	}
	glEnd();
}

void drawData(GraphParameters& gp) {

}

// Generates a point for each horizontal pixel, and joins them with lines
void drawFunction(GraphParameters &gp, Function* function) {
	glLineWidth(gp.lineWidth);
	int curveResolution = gp.width;
	glBegin(GL_LINES);
	
	// Draws the lines between each sample point on the curve of the function
	for (int i = 1; i < curveResolution; i++) {
		// Point 1 (R2)
		float horVal1 = (gp.minVisDomain + (abs(gp.maxVisDomain - gp.minVisDomain) * ((float)(i - 1) / curveResolution)));
		float verVal1 = function->evaluate('x', horVal1);

		// Point 2 (R2)
		float horVal2 = (gp.minVisDomain + (abs(gp.maxVisDomain - gp.minVisDomain) * ((float)i / curveResolution)));
		float verVal2 = function->evaluate('x', horVal2);
		
		// Point 1 (Normalized)
		float horPos1 = horVal1 / gp.maxVisDomain;
		float verPos1 = verVal1 / gp.maxVisRange;
		
		// Point 2 (Normalized)
		float horPos2 = horVal2 / gp.maxVisDomain;
		float verPos2 = verVal2 / gp.maxVisRange;

		// Give opengl the next two points to draw a line between
		glVertex2f(horPos1, verPos1);
		glVertex2f(horPos2, verPos2);
	}
	glEnd();
}

// Generates a point for each horizontal pixel, and joins them with lines
void drawVectorFunction(GraphParameters& gp, VectorFunction* function, float lo, float hi) {

	glLineWidth(gp.lineWidth);
	int curveResolution = gp.width;
	glBegin(GL_LINES);

	// Draws the lines between each sample point on the curve of the function
	for (int i = 1; i < curveResolution; i++) {
		// Point 1 (R2)
		float parameter1 = lo + ((hi - lo) * ((float)(i - 1) / curveResolution));
		float* p1 = function->evaluate('t', parameter1);

		// Point 2 (R2)
		float parameter2 = lo +   ((hi - lo) * ((float)(i) / curveResolution));
		float* p2 = function->evaluate('t', parameter2);
		
		// Point 1 (Normalized)
		float horPos1 = p1[0] / gp.maxVisDomain;
		float verPos1 = p1[1] / gp.maxVisRange;

		// Point 2 (Normalized)
		float horPos2 = p2[0] / gp.maxVisDomain;
		float verPos2 = p2[1] / gp.maxVisRange;

		// Give opengl the next two points to draw a line between
		glVertex2f(horPos1, verPos1);
		glVertex2f(horPos2, verPos2);
	}
	glEnd();
}

GLfloat* calculateVertices(char vars[], int resolution, int dim, Function* func, GraphParameters &gp) {
	int numOfScalars = dim * resolution * resolution;
	GLfloat* vertexArray = new GLfloat[numOfScalars];
	GLfloat xDif = gp.maxVisDomain - gp.minVisDomain;
	GLfloat yDif = gp.maxVisDomain - gp.minVisDomain;
	GLfloat xy[2];
	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
			GLfloat x = gp.minVisDomain + xDif * ((float)i / (resolution - 1));
			GLfloat y = gp.minVisDomain + yDif * ((float)j / (resolution - 1));;
			xy[0] = x;
			xy[1] = y;
			int k = i * resolution * dim + j * dim;
			vertexArray[k] = x;
			vertexArray[k + 1] = func->evaluate(vars, xy, 2);
			vertexArray[k + 2] = y;
		}
	}
	return vertexArray;
}

GLFWwindow* bootOpenGL(int width, int height) {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
	//GLFWwindow* window = glfwCreateWindow(width, height, "Grapher", NULL, NULL);
	GLFWwindow* window = glfwCreateWindow(width, height, "Grapher", glfwGetPrimaryMonitor(), NULL);
	glfwSetWindowPos(window, 0, 35);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewInit();
	return window;
}