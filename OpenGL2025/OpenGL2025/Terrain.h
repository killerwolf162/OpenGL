#pragma once
#include "Geometry.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Terrain
{
public:

	//textures
	GLuint normal;
	GLuint dirt;
	GLuint sand;
	GLuint grass;
	GLuint rock;
	GLuint snow;

	GLuint terrainVAO;
	GLuint terrainIndexCount;
	GLuint heightmapID;
	GLuint heightNormalID;
	GLenum format = GL_RGBA;
	int comp = 4.0f;
	int hScale = 100.0f;
	int xzScale = 5.0f;
	unsigned char* heightmapTex;
	unsigned char* heightNormalTex;
	const char* heightNormalmap;
	const char* heightmap;

	Terrain(const char* heightmap, const char* heightNormalmap);
	virtual ~Terrain();

	unsigned int generatePlain();
	void renderTerrain(GLuint program, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat, int season);


};

