#pragma once
#include "header.h"
#include "Shader.h"
#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "E_Direction6.h"
#include "Model.h"
#include "Tab.h"
#include "E_TextureID.h"
#include "RenderTarget.h"

class Renderer
{
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	// timing
	float _deltaTime = 0.0f;	// time between current frame and last frame
	float _lastFrame = 0.0f;

	GLFWwindow * _window;
	unsigned int _VBO;
	unsigned int _VAO;
	Tab<unsigned int> _textures;
	Shader * _shader;
	Camera * _camera;

	static void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void activateShader();
	void setShaderCamera();
	void clearScreen();
	void generateVertices(const RenderTarget & target);
	void setTexture(E_TextureID texture);
	void drawVertices(const RenderTarget & target);
	glm::vec3 convertVector(const Vector3f & v) const;
	Vector3f convertVector(const glm::vec3 & v) const;

public:
	Renderer();
	bool isWindowOpen();
	GLFWwindow * getWindow() const;
	void update();
	float getDeltaTime() const;
	void moveCamera(E_Direction6 direction, float deltaTime);
	void turnCamera(double xpos, double ypos);
	void zoomCamera(double offset);
	void draw(const std::list<const Model *> & models);
	~Renderer();
};