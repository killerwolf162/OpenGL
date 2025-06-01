#include "Terrain.h"
#include "stb_image.h"
#include "Util.h"

Terrain::Terrain(const char* heightmap, const char* heightNormalmap)
{
	this->heightmap = heightmap;
	this->heightNormalmap = heightNormalmap;


	dirt = Util::loadTexture("resources/textures/dirt.jpg");
	sand = Util::loadTexture("resources/textures/sand.jpg");
	grass = Util::loadTexture("resources/textures/grass.png", 4);
	rock = Util::loadTexture("resources/textures/rock.jpg");
	snow = Util::loadTexture("resources/textures/snow.jpg");
	heightNormalID = Util::loadTexture(heightNormalmap);
}

Terrain::~Terrain()
{
}

unsigned int Terrain::generatePlain()
{

	int width, height, channels;
	heightmapTex = nullptr;
	if (heightmap != nullptr) {
		heightmapTex = stbi_load(heightmap, &width, &height, &channels, comp);
		if (heightmapTex) {
			glGenTextures(1, &heightmapID);
			glBindTexture(GL_TEXTURE_2D, heightmapID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, heightmapTex);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	int stride = 8;
	float* vertices = new float[(width * height) * stride];
	unsigned int* indices = new unsigned int[(width - 1) * (height - 1) * 6];

	int index = 0;
	for (int i = 0; i < (width * height); i++) {
		// TODO: calculate x/z values
		int x = i % width;
		int z = i / width;

		float texHeight = heightmapTex[i * comp];

		// TODO: set position
		vertices[index++] = x * xzScale;
		vertices[index++] = (texHeight / 255.0f) * hScale;
		vertices[index++] = z * xzScale;

		// TODO: set normal
		vertices[index++] = 0;
		vertices[index++] = 1;
		vertices[index++] = 0;

		// TODO: set uv
		vertices[index++] = x / (float)width;
		vertices[index++] = z / (float)height;
	}

	// OPTIONAL TODO: Calculate normal
	// TODO: Set normal

	index = 0;
	for (int i = 0; i < (width - 1) * (height - 1); i++)
	{
		int x = i % (width - 1);
		int z = i / (width - 1);

		int vertex = z * width + x;

		indices[index++] = vertex;
		indices[index++] = vertex + width;
		indices[index++] = vertex + width + 1;

		indices[index++] = vertex;
		indices[index++] = vertex + width + 1;
		indices[index++] = vertex + 1;
	}

	unsigned int vertSize = (width * height) * stride * sizeof(float);
	terrainIndexCount = ((width - 1) * (height - 1) * 6);

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrainIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// vertex information!
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0);
	glEnableVertexAttribArray(0);
	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	delete[] vertices;
	delete[] indices;

	//stbi_image_free(heightmapTex);

	return VAO;
}

void Terrain::renderTerrain(GLuint program, glm::vec3 lightDir, glm::vec3 cameraPos, glm::mat4 viewMat, glm::mat4 projectionMat, int season)
{
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "mainTex"), 0);
	glUniform1i(glGetUniformLocation(program, "normalTex"), 1);
	glUniform1i(glGetUniformLocation(program, "dirt"), 2);
	glUniform1i(glGetUniformLocation(program, "sand"), 3);
	glUniform1i(glGetUniformLocation(program, "grass"), 4);
	glUniform1i(glGetUniformLocation(program, "rock"), 5);
	glUniform1i(glGetUniformLocation(program, "snow"), 6);

	glm::mat4 worldMat = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, glm::value_ptr(worldMat));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMat));

	// Make sure to set the light direction uniform
	glUniform3fv(glGetUniformLocation(program, "lightDirection"), 1, glm::value_ptr(lightDir));
	glUniform3fv(glGetUniformLocation(program, "cameraPosition"), 1, glm::value_ptr(cameraPos));

	glUniform1i(glGetUniformLocation(program, "season"), season);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, heightmapID);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, heightNormalID);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, dirt);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, sand);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, grass);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, rock);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, snow);

	glBindVertexArray(terrainVAO);
	glDrawElements(GL_TRIANGLES, terrainIndexCount, GL_UNSIGNED_INT, 0);


	glDisable(GL_DEPTH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}
