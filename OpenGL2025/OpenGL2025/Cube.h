#pragma once
#include "Geometry.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube
{
private:

	GLuint tex, normalTex;
	

	std::vector<float> vertices;
	std::vector<int> indicis;

	glm::vec3 worldPosition;
public:
	GLuint cubeVAO, cubeEBO;
	int cubeSize, cubeIndexCount;

	glm::mat4 world;
	glm::vec3 translateSpeed = glm::vec3(0, 0, 0);
	float rotationSpeed = 0.1f;

	Cube(std::vector<float> verts, std::vector<int> inds, const char* tex, const char* normalTex, glm::vec3 position, int scale = 1);
	virtual ~Cube();

	void rotate(float angle);
	void translate(glm::vec3 movementVec);
	void render(GLuint program);
};

