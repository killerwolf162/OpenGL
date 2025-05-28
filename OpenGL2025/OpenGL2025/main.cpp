#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Util.h"
#include "Geometry.h"
#include "Cube.h"
#include "Animations.h"
#include "stb_image.h"
#include "Terrain.h"
#include "model.h"

// Shaderprogram IDs
GLuint woodProgram;
GLuint metalProgram;
GLuint skyboxProgram;
GLuint terrainProgram;
GLuint modelProgram;
GLuint treeProgram;

// Box verices
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

// Box indicis
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

bool keys[1024];

// World Data
glm::vec3 lightDirection = glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f));
glm::vec3 cameraPosition = glm::vec3(900, 130, 1400);
glm::mat4 view, projection;

// Canera Movement
float lastX, lastY;
bool firstMouse = true;
float camYaw, camPitch;
glm::quat camQuat;

// forward dec
void setupBasicProgram(GLuint program, glm::vec3 lightPos, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat);
void renderSkyBox(GLuint program, GLuint VAO, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat, int indexCount);
void renderModel(Model* model, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, GLuint program, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat);

void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);

Model* backpack;
Model* house;
Model* table;
Model* chair;

int main()
{
	GLFWwindow* window;
	int res = Util::init(window, WIDTH, HEIGHT);
	if (res != 0) return res;

	stbi_set_flip_vertically_on_load(true);

	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwMakeContextCurrent(window);

	glm::vec3 position1 = glm::vec3(30, 10, 0);
	glm::vec3 position2 = glm::vec3(0, 10, 30);

	//setup terrain
	Terrain terrain("resources/textures/heightmap.png", "resources/textures/heightnormal.png");
	terrain.terrainVAO = terrain.generatePlain();

	// Setup box1
	Cube box(vertices, indicis, "resources/textures/box-texture-01.png", "resources/textures/box-texture-01-normal.png", position1, 50);
	box.translateSpeed = -glm::vec3(0.005f, 0.01f, 0);
	box.rotate(15.0f);

	// Setup box2
	Cube box2(vertices, indicis, "resources/textures/metalbox-texture-02.png", "resources/textures/metalbox-texture-02-normal.png", position2, 50);
	box2.translateSpeed = glm::vec3(0.02f, 0.01f, 0);
	box2.rotate(65.0f);

	// Setup model
	backpack = new Model("resources/models/backpack/backpack.obj");
	house = new Model("resources/models/house/house.obj");
	table = new Model("resources/models/table/table.obj");
	chair = new Model("resources/models/chair/chair.obj");

	// Create shaderprograms
	Util::createProgram(woodProgram, "resources/shaders/simpleVertex.shader", "resources/shaders/woodFragment.shader");
	Util::createProgram(metalProgram, "resources/shaders/simpleVertex.shader", "resources/shaders/metalFragment.shader");
	Util::createProgram(skyboxProgram, "resources/shaders/skyVertex.shader", "resources/shaders/skyFragment.shader");
	Util::createProgram(terrainProgram, "resources/shaders/terrainVertex.shader", "resources/shaders/terrainFragment.shader");
	Util::createProgram(modelProgram, "resources/shaders/modelVertex.shader", "resources/shaders/modelFragment.shader");

	// Create viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	// Matrices!
	view = glm::lookAt(cameraPosition, glm::vec3(800, 100, 1500), glm::vec3(0, 1, 1));
	projection = glm::perspective(glm::radians(90.0f), WIDTH / (float)HEIGHT, 0.1f, 5000.0f);

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		// Input 
		Util::processInput(window, keys, cameraPosition, view, camQuat);

		// Rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// les 4 skybox + terrain

		// Animate LightDirection
		//float t = glfwGetTime();
		//lightDirection = glm::normalize(glm::vec3(glm::sin(t), -0.5f, glm::cos(t)));
		
		renderSkyBox(skyboxProgram, box.cubeVAO, lightDirection, cameraPosition, view, projection, box.cubeIndexCount);
		terrain.renderTerrain(terrainProgram, lightDirection, cameraPosition, view, projection);

		// les 5 models
		
		float t = glfwGetTime();

		renderModel(backpack, glm::vec3(910, 112, 1420), glm::vec3(0, t, 0), glm::vec3(1, 1, 1), modelProgram, lightDirection, cameraPosition, view, projection);
		renderModel(house, glm::vec3(900, 100, 1400), glm::vec3(0, 0, 0), glm::vec3(10, 10, 10), modelProgram, lightDirection, cameraPosition, view, projection);
		renderModel(table, glm::vec3(909, 100, 1420), glm::vec3(0, 0, 0), glm::vec3(3, 3, 3), modelProgram, lightDirection, cameraPosition, view, projection);
		renderModel(chair, glm::vec3(910, 100, 1410), glm::vec3(0, 0, 0), glm::vec3(8, 8, 8), modelProgram, lightDirection, cameraPosition, view, projection);
		
		//Les 3 Programs + anims

		/* // Set wood program
		setupBasicProgram(woodProgram, lightDirection, cameraPosition, view, projection);
		box.render(woodProgram);
		Animations::movementInBoxAnim(box, 1, 1);

		// Set metal program
		setupBasicProgram(metalProgram, lightDirection, cameraPosition, view, projection);
		box2.render(metalProgram);
		Animations::movementInBoxAnim(box2, 2, 2); */

		// Swap & Poll
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void setupBasicProgram(GLuint program, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat)
{
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "mainTex"), 0);
	glUniform1i(glGetUniformLocation(program, "normalTex"), 1);

	glUniform3fv(glGetUniformLocation(program, "lightPosition"), 1, glm::value_ptr(lightDir));
	glUniform3fv(glGetUniformLocation(program, "cameraPosition"), 1, glm::value_ptr(cameraPos));

	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMat));
}

void renderModel(Model* model, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, GLuint program, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat)
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glUseProgram(program);

	glUniform1i(glGetUniformLocation(program, "texture_diffuse1"), 0);
	glUniform1i(glGetUniformLocation(program, "texture_specular1"), 1);
	glUniform1i(glGetUniformLocation(program, "texture_normal1"), 2);
	glUniform1i(glGetUniformLocation(program, "texture_roughness1"), 3);
	glUniform1i(glGetUniformLocation(program, "texture_ao1"), 4);

	glm::mat4 worldMat = glm::mat4(1.0f);
	worldMat = glm::translate(worldMat, pos);
	worldMat = worldMat * glm::toMat4(glm::quat(rot));
	worldMat = glm::scale(worldMat, scale);


	glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, glm::value_ptr(worldMat));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMat));

	glUniform3fv(glGetUniformLocation(program, "lightDirection"), 1, glm::value_ptr(lightDir));
	glUniform3fv(glGetUniformLocation(program, "cameraPosition"), 1, glm::value_ptr(cameraPos));

	model->Draw(program);

	glDisable(GL_BLEND);
}

void renderSkyBox(GLuint program, GLuint VAO, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat, int indexCount)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH);

	glUseProgram(program);

	glUniform3fv(glGetUniformLocation(program, "lightDirection"), 1, glm::value_ptr(lightDir));
	glUniform3fv(glGetUniformLocation(program, "cameraPosition"), 1, glm::value_ptr(cameraPos));

	glm::mat4 worldMat = glm::mat4(1.0f);
	worldMat = glm::translate(worldMat, cameraPos);
	worldMat = glm::scale(worldMat, glm::vec3(10, 10, 10));

	glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, glm::value_ptr(worldMat));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMat));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float x = (float)xpos;
	float y = (float)ypos;

	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float dx = x - lastX;
	float dy = y - lastY;
	lastX = x;
	lastY = y;

	camYaw -= dx;
	camPitch = glm::clamp(camPitch - dy, -89.9f, 89.9f);

	if (camYaw >= 180) camYaw -= 360;
	if (camYaw <= -180) camYaw += 360;

	camQuat = glm::quat(glm::vec3(glm::radians(camPitch), glm::radians(camYaw), 0));

	glm::vec3 camForward = camQuat * glm::vec3(0, 0, 1);
	glm::vec3 camUp = camQuat * glm::vec3(0, 1, 0);

	view = glm::lookAt(cameraPosition, cameraPosition + camForward, camUp);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	if (action == GLFW_PRESS)
	{
		// store key is pressed
		keys[key] = true;
	}

	else if (action == GLFW_RELEASE)
	{
		// store key is released
		keys[key] = false;
	}

}
