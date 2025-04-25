#pragma once
#include "Geometry.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube
{
private:

public:

	GLuint cubeVAO, cubeEBO;
	GLuint tex, normalTex;

	int cubeSize, cubeIndexCount;

	std::vector<float> vertices;
	std::vector<int> indicis;

	glm::mat4 world;
	glm::vec3 worldPosition;

	Cube(std::vector<float> verts, std::vector<int> inds, const char* tex, const char* normalTex, glm::vec3 position);
	void rotate(float angle);

	~Cube();

};

