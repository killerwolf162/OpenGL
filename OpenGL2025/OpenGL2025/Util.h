#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "model.h"

class Util
{
public:
	static int init(GLFWwindow*& window, int width, int height);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos, float& lastX, float& lastY, float& yaw, float& pitch, bool firstTime);
	static void processInput(GLFWwindow* window, bool keys[1024], glm::vec3& camPos, glm::mat4& viewMat, glm::quat camQuat);
	static void loadFile(const char* filename, char*& output);
	static void createProgram(GLuint& programID, const char* vertex, const char* fragment);
	static GLuint loadTexture(const char* path, int comp = 0);
	static void setupBasicProgram(GLuint program, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat);
	static void setupModelProgram(GLuint program, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat);
	static void renderModel(GLuint program, Model* model, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	static void renderSkybox(GLuint program, GLuint VAO, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat, int indexCount);
};

