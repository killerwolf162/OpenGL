#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Util.h"
#include "Geometry.h"
#include "Cube.h"
#include "Animations.h"

// Program IDs
GLuint woodProgram;
GLuint metalProgram;

std::vector<float> vertices
{
	// positions            //colors            // tex coords   // normals          //tangents      //bitangents
	0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,   1.f, 1.f,       0.f, -1.f, 0.f,     -1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
	0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   1.f, 0.f,       0.f, -1.f, 0.f,     -1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
	-0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,   0.f, 0.f,       0.f, -1.f, 0.f,     -1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
	-0.5f, -0.5f, -.5f,     1.0f, 1.0f, 1.0f,   0.f, 1.f,       0.f, -1.f, 0.f,     -1.f, 0.f, 0.f,  0.f, 0.f, 1.f,

	0.5f, 0.5f, -0.5f,      1.0f, 1.0f, 1.0f,   1.f, 1.f,       1.f, 0.f, 0.f,     0.f, -1.f, 0.f,  0.f, 0.f, 1.f,
	0.5f, 0.5f, 0.5f,       1.0f, 1.0f, 1.0f,   1.f, 0.f,       1.f, 0.f, 0.f,     0.f, -1.f, 0.f,  0.f, 0.f, 1.f,

	0.5f, 0.5f, 0.5f,       1.0f, 1.0f, 1.0f,   1.f, 0.f,       0.f, 0.f, 1.f,     1.f, 0.f, 0.f,  0.f, -1.f, 0.f,
	-0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   0.f, 0.f,       0.f, 0.f, 1.f,     1.f, 0.f, 0.f,  0.f, -1.f, 0.f,

	-0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   0.f, 0.f,      -1.f, 0.f, 0.f,     0.f, 1.f, 0.f,  0.f, 0.f, 1.f,
	-0.5f, 0.5f, -.5f,      1.0f, 1.0f, 1.0f,   0.f, 1.f,      -1.f, 0.f, 0.f,     0.f, 1.f, 0.f,  0.f, 0.f, 1.f,

	-0.5f, 0.5f, -.5f,      1.0f, 1.0f, 1.0f,   0.f, 1.f,      0.f, 0.f, -1.f,     1.f, 0.f, 0.f,  0.f, 1.f, 0.f,
	0.5f, 0.5f, -0.5f,      1.0f, 1.0f, 1.0f,   1.f, 1.f,      0.f, 0.f, -1.f,     1.f, 0.f, 0.f,  0.f, 1.f, 0.f,

	-0.5f, 0.5f, -.5f,      1.0f, 1.0f, 1.0f,   1.f, 1.f,       0.f, 1.f, 0.f,     1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
	-0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   1.f, 0.f,       0.f, 1.f, 0.f,     1.f, 0.f, 0.f,  0.f, 0.f, 1.f,

	0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   1.f, 1.f,       0.f, 0.f, 1.f,     1.f, 0.f, 0.f,  0.f, -1.f, 0.f,
	-0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,   0.f, 1.f,       0.f, 0.f, 1.f,     1.f, 0.f, 0.f,  0.f, -1.f, 0.f,

	-0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,   1.f, 0.f,       -1.f, 0.f, 0.f,     0.f, 1.f, 0.f,  0.f, 0.f, 1.f,
	-0.5f, -0.5f, -.5f,     1.0f, 1.0f, 1.0f,   1.f, 1.f,       -1.f, 0.f, 0.f,     0.f, 1.f, 0.f,  0.f, 0.f, 1.f,

	-0.5f, -0.5f, -.5f,     1.0f, 1.0f, 1.0f,   0.f, 0.f,       0.f, 0.f, -1.f,     1.f, 0.f, 0.f,  0.f, 1.f, 0.f,
	0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,   1.f, 0.f,       0.f, 0.f, -1.f,     1.f, 0.f, 0.f,  0.f, 1.f, 0.f,

	0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,   0.f, 1.f,       1.f, 0.f, 0.f,     0.f, -1.f, 0.f,  0.f, 0.f, 1.f,
	0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   0.f, 0.f,       1.f, 0.f, 0.f,     0.f, -1.f, 0.f,  0.f, 0.f, 1.f,

	0.5f, 0.5f, -0.5f,      1.0f, 1.0f, 1.0f,   0.f, 1.f,       0.f, 1.f, 0.f,     1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
	0.5f, 0.5f, 0.5f,       1.0f, 1.0f, 1.0f,   0.f, 0.f,       0.f, 1.f, 0.f,     1.f, 0.f, 0.f,  0.f, 0.f, 1.f
};

std::vector<int> indicis
{  // note that we start from 0!
	// DOWN
	0, 1, 2,   // first triangle
	0, 2, 3,    // second triangle
	// BACK
	14, 6, 7,   // first triangle
	14, 7, 15,    // second triangle
	// RIGHT
	20, 4, 5,   // first triangle
	20, 5, 21,    // second triangle
	// LEFT
	16, 8, 9,   // first triangle
	16, 9, 17,    // second triangle
	// FRONT
	18, 10, 11,   // first triangle
	18, 11, 19,    // second triangle
	// UP
	22, 12, 13,   // first triangle
	22, 13, 23,    // second triangle
};

const int WIDTH = 1280;
const int HEIGHT = 720;

int main()
{
	GLFWwindow* window;
	int res = Util::init(window, WIDTH, HEIGHT);
	if (res != 0) return res;

	glm::vec3 position1 = glm::vec3(-1, 0, 0);
	glm::vec3 position2 = glm::vec3(2, 0, 0);

	Cube box(vertices, indicis, "textures/box-texture-01.png", "textures/box-texture-01-normal.png", position1);
	box.rotate(15.0f);
	box.translateSpeed = -box.translateSpeed;

	Cube box2(vertices, indicis, "textures/box-texture-01.png", "textures/box-texture-01-normal.png", position2);
	box2.rotate(65.0f);

	Util::createProgram(woodProgram, "shaders/simpleVertex.shader", "shaders/simpleFragment.shader");

	// Set texture channels
	glUseProgram(woodProgram);
	glUniform1i(glGetUniformLocation(woodProgram, "mainTex"), 0);
	glUniform1i(glGetUniformLocation(woodProgram, "normalTex"), 1);

	// Create viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	glm::vec3 lightPosition = glm::vec3(2, 2, 3.0f);
	glm::vec3 cameraPosition = glm::vec3(0, 0, 5.0f);

	//matrices!

	glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 1));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		// Input 
		Util::processInput(window);

		// Rendering

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform3fv(glGetUniformLocation(woodProgram, "lightPosition"), 1, glm::value_ptr(lightPosition));
		glUniform3fv(glGetUniformLocation(woodProgram, "cameraPosition"), 1, glm::value_ptr(cameraPosition));

		glUniformMatrix4fv(glGetUniformLocation(woodProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(woodProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		box.render(woodProgram);
		Animations::basicAnim(box);

		box2.render(woodProgram);
		Animations::basicAnim(box2);
		
		// Swap & Poll
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}