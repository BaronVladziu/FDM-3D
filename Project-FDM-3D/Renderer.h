#pragma once
#include "header.h"
#include "Shader.h"
#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	GLFWwindow * window;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int texture;
	Shader * ourShader;
	Camera * camera;

	static void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void generateVertices(const std::list<Renderable *> & renderables);
	void drawVertices(const glm::vec3 & translation, float angle, const glm::vec3 & axis, unsigned int numberOfVertices);

public:
	Renderer();
	bool isWindowOpen();
	void draw(const std::list<Renderable *> & renderables);
	~Renderer();
};