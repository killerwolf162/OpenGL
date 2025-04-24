#include <iostream>
#include <vector>
#include "Util.h"
#include "Triangle.h"

void createShaders();

// Program IDs
GLuint simpleProgram;

std::vector<float> trianglesVertices
{
	// position						//color
	-0.1f, -0.1f, 0.0f,	/*0*/		0.3f, .0f, .0f, 1.0f,
	0.1f, -0.1f, 0.0f,	/*1*/		0.3f, .0f, .0f, 1.0f,
	0.0f, 0.2f, 0.0f,	/*2*/		0.3f, .0f, .0f, 1.0f,

	-0.5f, -0.25f, 0.0f,/*3*/		0.0f, .0f, .0f, 1.0f,
	-0.4f, -0.7f, 0.0f,	/*4*/		0.0f, .0f, .0f, 1.0f,
	-0.3f, -0.25f, 0.0f,/*5*/		0.0f, .0f, .0f, 1.0f,
	-0.2f, -0.7f, 0.0f,	/*6*/		0.0f, .0f, .0f, 1.0f,
	-0.1f, -0.25f, 0.0f,/*7*/		0.0f, .0f, .0f, 1.0f,
	0.0f, -0.7f, 0.0f,	/*8*/		0.0f, .0f, .0f, 1.0f,
	0.1f, -0.25f, 0.0f,	/*9*/		0.0f, .0f, .0f, 1.0f,
	0.2f, -0.70f, 0.0f,	/*10*/		0.0f, .0f, .0f, 1.0f,
	0.3f, -0.25f, 0.0f,	/*11*/		0.0f, .0f, .0f, 1.0f,
	0.4f, -0.70f, 0.0f,	/*12*/		0.0f, .0f, .0f, 1.0f,
	0.5f, -0.25f, 0.0f,	/*13*/		0.0f, .0f, .0f, 1.0f,

	-0.4f, 0.2f, 0.0f,	/*14*/		1.0f, 0.0f, 0.0f, 1.0f,
	-0.2f, 0.2f, 0.0f,	/*15*/		1.0f, 0.0f, 0.0f, 1.0f,
	-0.2f, 0.5f, 0.0f,	/*16*/		1.0f, 0.0f, 0.0f, 1.0f,
	-0.4f, 0.5f, 0.0f,	/*17*/		1.0f, 0.0f, 0.0f, 1.0f,

	0.4f, 0.2f, 0.0f,	/*18*/		1.0f, 0.0f, 0.0f, 1.0f,
	0.2f, 0.2f, 0.0f,	/*19*/		1.0f, 0.0f, 0.0f, 1.0f,
	0.2f, 0.5f, 0.0f,	/*20*/		1.0f, 0.0f, 0.0f, 1.0f,
	0.4f, 0.5f, 0.0f,	/*17*/		1.0f, 0.0f, 0.0f, 1.0f,

	-0.5f, -0.7f, 0.0f, /*19*/		0.6f, 0.0f, 0.0f,1.0f,
	 0.5f, -0.7f, 0.0f,	/*20*/		0.6f, 0.0f, 0.0f,1.0f,
	 0.5f, -0.25f, 0.0f,/*22*/		0.6f, 0.0f, 0.0f,1.0f,
	-0.5f, -0.25f, 0.0f,/*22*/		0.6f, 0.0f, 0.0f,1.0f,
};

std::vector<int> triangleIndicis
{
	14,15,16, // squares
	14,16,17,

	18,19,20,
	18,20,21,

	22,23,24,
	22,24,25,

	0,1,2, // triangles
	3,4,5,
	5,6,7,
	7,8,9,
	9,10,11,
	11,12,13
};


int main()
{
	GLFWwindow* window;
	int res = Util::init(window);
	if (res != 0) return res;

	GLuint triangleVAO, triangleEBO;
	int trianglesSize, triangleIndexCount;
	Triangle::createTriangles(triangleVAO, triangleEBO, trianglesSize, triangleIndexCount, trianglesVertices, triangleIndicis);
	Util::createProgram(simpleProgram, "shaders/simpleVertex.shader", "shaders/simpleFragment.shader");

	// Create viewport
	glViewport(0, 0, 1280, 720);

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		// Input 
		Util::processInput(window);

		// Rendering

		glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(simpleProgram);

		glBindVertexArray(triangleVAO);
		glDrawElements(GL_TRIANGLES, triangleIndexCount, GL_UNSIGNED_INT, 0);

		// Swap & Poll
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void createShaders()
{
	Util::createProgram(simpleProgram, "shaders/simpleVertex.shader", "shaders/simpleFragment.shader");
}