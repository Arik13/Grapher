#define _USE_MATH_DEFINES

#include <cmath>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include <iostream>
#include <time.h>
#include "Parser.h"
#include "Drawer.h"
#include "Function.h"
#include "VectorFunction.h"
#include "Controls.h"
#include "VAO.h"
#include "MeshGenerators.h"
#include "DiskIO.h"

int main(void) {
	///____________________________________________________________________________________________________________________
	// Place to input functions as strings
	std::string f1 = "x+y";
	std::string f2 = "sin(10*(x^2+y^2))/10";
	std::string f3 = "(x/2)^2-0.1*y^2";
	std::string f4 = "sin(x+y)";
	std::string f5 = "(x^2+y^2)^(1/2)";
	std::string f6 = "x^(1/2)";
	std::string f7 = "x^4+y^4-4*x*y+4";
	
	Function* f = parseFunction(f7);
	
	std::string var = "x";
	int n = 2;
	char* vars = new char[n];
	float* values = new float[n];
	vars[0] = 'x';
	vars[1] = 'y';
	values[0] = M_PI/2;
	values[1] = 0;

	//Function* fx = f->tangentPlane(vars, values, n);
	std::cout << "Function: " << f->name() << std::endl;
	//std::cout << "Derivative: " << fx->name() << std::endl;
	// Parse strings into function objects
	std::vector<Function*> functions;
	functions.push_back(f);
	//functions.push_back(fx);
	
	GraphParameters gp;
	GLFWwindow* window = bootOpenGL(gp.width, gp.height);
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);			// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// Hide the mouse and enable unlimited mouvement
	glfwPollEvents();												// Set the mouse at the center of the screen
	glfwSetCursorPos(window, gp.width / 2, gp.height / 2);

	///____________________________________________________________________________________________________________________
	//MeshObject* axes = loadAxes(100);
	MeshObject* graph = generateGraph(gp, functions[0]);		// Load graph mesh
	//MeshObject* graphD = generateGraph(gp, functions[1]);		// Load graph mesh
	
	// Init OpenGL resources
	VAO* graphVAO = new VAO(	
		graph->vertices, 
		graph->colors,
		graph->indices,
		graph->vBytes,
		graph->cBytes,
		graph->iBytes);
	/*VAO* graphDVAO = new VAO(
		graphD->vertices,
		graphD->colors,
		graphD->indices,
		graphD->vBytes,
		graphD->cBytes,
		graphD->iBytes);*/
	/*VAO* axesVAO = new VAO(
		axes->vertices, 
		axes->colors, 
		axes->indices, 
		axes->vBytes, 
		axes->cBytes, 
		axes->iBytes);*/

	///____________________________________________________________________________________________________________________
	// Get handles for our "MVP" uniforms
	GLuint axisProgram = LoadShaders("VertexShader.glsl","FragmentShader.glsl");
	GLuint axisMatrixID = glGetUniformLocation(axisProgram, "MVP");

	const int PBO_COUNT = 2;

	// global variables
	/*GLuint pboIds[PBO_COUNT];           // IDs of PBOs
	const int DATA_SIZE = 9000 * 900 * sizeof(GLfloat);
	const GLenum PIXEL_FORMAT = GL_DEPTH_COMPONENT; // depth buffer
	glGenBuffers(PBO_COUNT, pboIds);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[0]);
	glBufferData(GL_PIXEL_PACK_BUFFER, DATA_SIZE, 0, GL_STREAM_READ);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[1]);
	glBufferData(GL_PIXEL_PACK_BUFFER, DATA_SIZE, 0, GL_STREAM_READ);

	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);*/

	///____________________________________________________________________________________________________________________
	// Rendering Loop
	glEnable(GL_DEPTH_TEST);
	int index = 0;
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		// Poll the window for its width and height
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		
		// Create MVP matrix
		computeMatricesFromInputs(window, width, height);
		glm::mat4 Projection = getProjectionMatrix();
		glm::mat4 View = getViewMatrix();
		glm::mat4 Model = glm::mat4(1.0);
		glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

		// Set the viewport area 
		glViewport(0, 0, width, height);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Draw Axes
		/*glUseProgram(axisProgram);
		glUniformMatrix4fv(axisMatrixID, 1, GL_FALSE, &MVP[0][0]);
		glBindVertexArray(axesVAO->ID());
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, (void*)0);*/

		// Draw Graph
		glUseProgram(axisProgram);
		glUniformMatrix4fv(axisMatrixID, 1, GL_FALSE, &MVP[0][0]);
		glBindVertexArray(graphVAO->ID());
		glDrawElements(GL_LINES, graph->iBytes, GL_UNSIGNED_SHORT, (void*)0);
		
		//glBindVertexArray(graphDVAO->ID());
		//glDrawElements(GL_LINES, graphD->iBytes, GL_UNSIGNED_SHORT, (void*)0);
		
		//glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[index]);
		//glReadPixels(0, 0, width, height, PIXEL_FORMAT, GL_FLOAT, 0);
		//index++;
		//index = index % 2;
		//writeBufferToDisk();

		glBindVertexArray(0);
		glUseProgram(0);

		// Swap buffer and check for events
		glfwSwapBuffers(window);
		glfwPollEvents();
		glFinish();
	}
	// Cleanup
	glDeleteProgram(axisProgram);
	glfwDestroyWindow(window);
	glfwTerminate;
	//exit(EXIT_SUCCESS);
}