#include "Util.h"
#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int Util::init(GLFWwindow*& window, const int width, const int height)
{
	//GLFW Init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Make Window and Active Context
	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}

void Util::mouseCallback(GLFWwindow* window, double xpos, double ypos, float& lastX, float& lastY, float& yaw, float& pitch, bool firstTime)
{
	float x = (float)xpos;
	float y = (float)ypos;

	if (firstTime)
	{
		lastX = x;
		lastY = y;
	}

	float dx = x - lastX;
	float dy = y - lastY;
	lastX = x;
	lastY = y;

	yaw += dx;
	pitch = glm::clamp(pitch + dy, -89.9f, 89.9f);

	if (yaw >= 180) yaw -= 360;
	if (yaw <= -180) yaw += 360;
}

void Util::processInput(GLFWwindow* window, bool keys[1024], glm::vec3& camPos, glm::mat4& viewMat, glm::quat camQuat)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	bool camChanged = false;

	if (keys[GLFW_KEY_W])
	{
		camPos += camQuat * glm::vec3(0, 0, 1);
		camChanged = true;
	}
	if (keys[GLFW_KEY_S])
	{
		camPos += camQuat * glm::vec3(0, 0, -1);
		camChanged = true;
	}
	if (keys[GLFW_KEY_A])
	{
		camPos += camQuat * glm::vec3(1, 0, 0);
		camChanged = true;
	}
	if (keys[GLFW_KEY_D])
	{
		camPos += camQuat * glm::vec3(-1, 0, 0);
		camChanged = true;
	}
	if (camChanged)
	{
		glm::vec3 camForward = camQuat * glm::vec3(0, 0, 1);
		glm::vec3 camUp = camQuat * glm::vec3(0, 1, 0);
		viewMat = glm::lookAt(camPos, camPos + camForward, camUp);
	}
}

void Util::loadFile(const char* filename, char*& output)
{
	//open file
	std::ifstream file(filename, std::ios::binary);

	if (file.is_open())
	{
		//get length of file
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		// allocate memory for char pointer
		output = new char[length + 1];

		// read data as block
		file.read(output, length);

		// add null terminator to end of char pointer
		output[length] = '\0';

		file.close();
	}
	else
	{
		output = NULL;
	}
}

void Util::createProgram(GLuint& programID, const char* vertex, const char* fragment)
{
	// Create a GL Program with a Vertex & Fragment Shader
	char* vertexSrc;
	char* fragmentSrc;
	Util::loadFile(vertex, vertexSrc);
	Util::loadFile(fragment, fragmentSrc);

	GLuint vertexShaderID, fragmentShaderID;

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShaderID);

	int success;
	char infolog[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderID, 512, nullptr, infolog);
		std::cout << "ERROR COMPILING VERTEX SHADER\n" << infolog << std::endl;
	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShaderID);


	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infolog);
		std::cout << "ERROR COMPILING FRAGMENT SHADER\n" << infolog << std::endl;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, nullptr, infolog);
		std::cout << "ERROR LINKING PROGRAM\n" << infolog << std::endl;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	delete vertexSrc;
	delete fragmentSrc;
}

GLuint Util::loadTexture(const char* path, int comp)
{
	GLuint textureID;

	int width, height, numChannels;
	unsigned char* data = stbi_load(path, &width, &height, &numChannels, comp);

	if (data)
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (comp != 0) numChannels = comp;
		if (numChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (numChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error loading texture: " << path << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}
