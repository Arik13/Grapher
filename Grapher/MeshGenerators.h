#pragma once
#include <GLEW/glew.h>

struct MeshObject {
	GLfloat* vertices;
	GLfloat* colors;
	GLushort* indices;
	int vBytes;
	int cBytes;
	int iBytes;
};

MeshObject* generateAxes(float axisLength) {
	GLfloat axesVertices[] = {
			axisLength, 0, 0,
			-axisLength, 0, 0,
			0, axisLength, 0,
			0, -axisLength, 0,
			0, 0, axisLength,
			0, 0, -axisLength
	};
	GLfloat axesColors[] = {
		1, 0, 0, 1,
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1,
		0, 0, 1, 1
	};

	GLushort axesIndices[] = {
		0, 1, 2, 3, 4, 5
	};
	MeshObject axes;
	axes.vertices = axesVertices;
	axes.colors = axesColors;
	axes.indices = axesIndices;
	axes.vBytes = sizeof(axesVertices);
	axes.cBytes = sizeof(axesColors);
	axes.iBytes = sizeof(axesIndices);
	return &axes;
}
MeshObject* generateGraph(GraphParameters gp, Function* function) {
	// Get sampling of vertices from the function
	char vars[] = { 'x', 'y' };
	float domain[] = { -5.0f, 5.0f, -5.0f, 5.0f };
	const int resolution = 200;
	const int dim = 3;
	//std::cout << "Got to vertex calculation" << std::endl;
	GLfloat* graphVertices = calculateVertices(vars, resolution, dim, function, gp);
	int numOfVertices = resolution * resolution;
	const int numOfColors = resolution * resolution * (dim + 1);
	GLfloat* graphColors = new GLfloat[numOfColors];

	// Calculate the graph colors
	float colorSensitivity = 10;
	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
			int k = i * resolution * dim + j * dim;
			int l = i * resolution * (dim + 1) + j * (dim + 1);
			float relativeZ = graphVertices[k + 1] / (1 / colorSensitivity);
			graphColors[l] = (relativeZ <= 0) ? abs(relativeZ) : 0;
			graphColors[l + 1] = 1 - abs(relativeZ);
			graphColors[l + 2] = (relativeZ >= 0) ? relativeZ : 0;
			graphColors[l + 3] = 1;
		}
	}

	// Calculate the indices that describe a grid of the graph vertices
	const int indicesPerLine = 2;
	const int linesPerTrace = resolution - 1;
	const int tracesPerDim = resolution;
	const int indicesPerGraph = indicesPerLine * linesPerTrace * tracesPerDim * 2;
	GLushort* graphIndices = new GLushort[indicesPerGraph];

	// Calculate the indices representing the traces in the x direction
	for (int trace = 0; trace < tracesPerDim; trace++) {
		for (int line = 0; line < linesPerTrace; line++) {
			int k = line * indicesPerLine + trace * linesPerTrace * indicesPerLine;
			int l = line + trace * linesPerTrace + trace;
			graphIndices[k] = l;
			graphIndices[k + 1] = l + 1;
		}
	}

	// calculate the indices representing the traces in the y direction
	const int sI = indicesPerGraph / 2;
	for (int trace = 0; trace < tracesPerDim; trace++) {
		for (int line = 0; line < linesPerTrace; line++) {
			int k = line * indicesPerLine + trace * linesPerTrace * indicesPerLine;
			int l = k / 2;
			graphIndices[sI + k] = l;
			graphIndices[sI + k + 1] = l + tracesPerDim;
		}
	}
	MeshObject* graph = new MeshObject();
	graph->vertices = graphVertices;
	graph->colors = graphColors;
	graph->indices = graphIndices;
	graph->vBytes = numOfVertices * sizeof(GLfloat) * dim;
	graph->cBytes = numOfColors * sizeof(GLfloat);
	graph->iBytes = indicesPerGraph * sizeof(GLushort);
	return graph;
}