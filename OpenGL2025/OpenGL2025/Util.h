#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
static class Util
{
public:
	static int init(GLFWwindow*& window, int width, int height);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos, float& lastX, float& lastY, float& yaw, float& pitch, bool firstTime);
	static void processInput(GLFWwindow* window);
	static void loadFile(const char* filename, char*& output);
	static void createProgram(GLuint& programID, const char* vertex, const char* fragment);
	static GLuint loadTexture(const char* path);
};

