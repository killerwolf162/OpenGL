#include "Cube.h"
#include "Geometry.h"
#include "Util.h"

Cube::Cube(std::vector<float> verts, std::vector<int> inds, const char* tex, const char* normalTex, glm::vec3 position)
{
	this->vertices = verts;
	this->indicis = inds;
	this->tex = Util::loadTexture(tex);
	this->normalTex = Util::loadTexture(normalTex);
	this->worldPosition = position;

	Geometry::createGeometryTBN(cubeVAO, cubeEBO, cubeSize, cubeIndexCount, vertices, indicis);

	world = glm::mat4(1.0f);
	world = glm::rotate(world, glm::radians(0.0f), glm::vec3(0, 1, 0));
	world = glm::scale(world, glm::vec3(1, 1, 1));
	world = glm::translate(world, worldPosition);

}

void Cube::rotate(float angle)
{
	world = glm::rotate(world, glm::radians(angle), glm::vec3(0, 1, 0));
}

void Cube::render(GLuint program)
{
	glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, glm::value_ptr(world));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalTex);

	glBindVertexArray(cubeVAO);
	glDrawElements(GL_TRIANGLES, cubeIndexCount, GL_UNSIGNED_INT, 0);
}

Cube::~Cube()
{
}
