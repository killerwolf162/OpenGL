#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
static class Util
{
public:
	static int init(GLFWwindow*& window);
	static void processInput(GLFWwindow* window);
	static void loadFile(const char* filename, char*& output);
	static void createProgram(GLuint& programID, const char* vertex, const char* fragment);
};

