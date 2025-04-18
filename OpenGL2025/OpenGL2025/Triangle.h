#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

static class Triangle
{
public:
	static void createTriangle(GLuint& VAO, int& size, std::vector<float>& vertices);
	static void createTriangles(GLuint& VAO, GLuint& EBO, int& size, int& numIndices, std::vector<float>& vertices, std::vector<int>& indicis);

};

