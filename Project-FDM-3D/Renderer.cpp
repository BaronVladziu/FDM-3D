#include "header.h"
#include "Renderer.h"
#include "Camera.h"
#include "Renderable.h"
#include "Tab.h"
#include "RenderVertex.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
void Renderer::activateShader() {
	_shader->use();
}
void Renderer::setShaderCamera() {
	glm::mat4 projection = glm::perspective(glm::radians(_camera->getFov()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	_shader->setMat4("projection", projection);
	glm::mat4 view = glm::lookAt(_camera->getPos(), _camera->getPos() + _camera->getFront(), _camera->getUp());
	_shader->setMat4("view", view);
}
void Renderer::clearScreen() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::generateVertices(const RenderTarget & target) {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	int verticesDataLength = 5 * target.getNumberOfVertices();
	float * vertices = new float[verticesDataLength];
	int actDataIndex = 0;
	const Tab<RenderVertex> tab = target.generateRenderVertices();
	for (int vertex = 0; vertex < tab.getSize(); vertex++) {
		float * vertexValues = tab[vertex].getData();
		for (int number = 0; number < 5; number++) {
			vertices[actDataIndex++] = vertexValues[number];
		}
	}
	glBufferData(GL_ARRAY_BUFFER, verticesDataLength * sizeof(float), vertices, GL_STATIC_DRAW);
	delete[] vertices;
}
void Renderer::setTexture(E_TextureID texture) {
	glDisable(GL_CULL_FACE);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// bind texture on corresponding texture units
	glBindTexture(GL_TEXTURE_2D, _textures[int(texture)]);
}
glm::vec3 Renderer::convertVector(const Vector3f & v) const {
	return glm::vec3(v.x, v.y, v.z);
}
Vector3f Renderer::convertVector(const glm::vec3 & v) const {
	return Vector3f(v.x, v.y, v.z);
}

Renderer::Renderer()
	: _textures(4)
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project-FDM-3D (PreAlpha)", NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, Renderer::framebuffer_size_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	_shader = new Shader("shader.vs", "shader.fs");
	//create camera
	_camera = new Camera(_window);

	// create & bind buffers
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	activateShader();
	for (int i = 0; i < _textures.getSize(); i++) {
		// load and create a texture
		glGenTextures(1, &_textures[i]);
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char *data = NULL;
		switch ((E_TextureID)i) {
		case E_TextureID::Plane:
			data = stbi_load("Textures/Rectangle.png", &width, &height, &nrChannels, 0);
			break;
		case E_TextureID::Marked:
			data = stbi_load("Textures/Marked.png", &width, &height, &nrChannels, 0);
			break;
		case E_TextureID::Target:
			data = stbi_load("Textures/Target.png", &width, &height, &nrChannels, 0);
			break;
		case E_TextureID::Speaker:
			data = stbi_load("Textures/Speaker.png", &width, &height, &nrChannels, 0);
			break;
		default:
			std::cout << "Error: Unsupported texture ID!" << std::endl;
		}

		if (data != NULL && data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Error: Failed to load texture!" << std::endl;
		}
		stbi_image_free(data);

		// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
		_shader->setInt("texture" + std::to_string(i), i);
	}
}
bool Renderer::isWindowOpen() {
	return !glfwWindowShouldClose(_window);
}
GLFWwindow * Renderer::getWindow() const {
	return _window;
}
void Renderer::update() {
	// per-frame time logic
	float currentFrame = (float)glfwGetTime();
	_deltaTime = currentFrame - _lastFrame;
	_lastFrame = currentFrame;
}
float Renderer::getDeltaTime() const {
	return _deltaTime;
}
void Renderer::moveCamera(E_Direction6 direction, float deltaTime) {
	_camera->move(direction, deltaTime);
}
void Renderer::turnCamera(double xpos, double ypos) {
	_camera->turn(xpos, ypos);
}
void Renderer::zoomCamera(double offset) {
	_camera->zoom(offset);
}
void Renderer::draw(const std::list<const Model *> & models) {
	setShaderCamera();
	clearScreen();
	//Creating RenderTargets
	std::list<RenderTarget> renderTargets;
	for (const Model * model : models) {
		const std::list<Renderable *> & modelPlanes = model->getPlanes();
		glm::vec3 position = convertVector(model->getPosition());
		glm::vec3 positionFromCamera = position - _camera->getPos();
		glm::vec3 scale = convertVector(model->getScale());
		//Scaling
		if (model->isAutoscaled()) {
			scale *= glm::length(positionFromCamera);
		}
		//Rotating
		float rotation = model->getRotation();
		if (model->isAutorotated()) {
			glm::vec3 flatPositionFromCamera = glm::vec3(positionFromCamera.x, 0.f, positionFromCamera.z);
			glm::vec3 normalizedFlatPositionFromCamera = glm::normalize(flatPositionFromCamera);
			float yaw = glm::degrees(glm::acos(glm::dot(normalizedFlatPositionFromCamera, glm::vec3(0.f, 0.f, 1.f))));
			glm::vec3 flatCross = glm::cross(normalizedFlatPositionFromCamera, glm::vec3(0.f, 0.f, 1.f));
			if (flatCross.y > 0) {
				yaw = 180 - yaw;
			}
			glm::vec3 normalizedPositionFromCamera = glm::normalize(positionFromCamera);
			glm::vec3 pitchAxis = glm::cross(normalizedPositionFromCamera, normalizedFlatPositionFromCamera);
			glm::vec3 normalizedPitchAxis = glm::normalize(pitchAxis);
			float pitch = -glm::degrees(glm::acos(glm::dot(normalizedPositionFromCamera, normalizedFlatPositionFromCamera)));
			for (Renderable * renderable : modelPlanes) {
				renderTargets.push_back(RenderTarget(renderable, position, yaw, pitch, normalizedPitchAxis, scale));
			}
		}
		else {
			glm::vec3 rotationAxis = convertVector(model->getRotationAxis());
			for (Renderable * renderable : modelPlanes) {
				renderTargets.push_back(RenderTarget(renderable, position, rotation, rotationAxis, scale));
			}
		}
	}
	//Sorting to make transparency work
	//TODO
	//Drawing RenderTargets
	for (const RenderTarget & target : renderTargets) {
		generateVertices(target);
		setTexture(target.getTexture());
		activateShader();
		glBindVertexArray(_VAO);
		drawVertices(target);
	}
	glfwSwapBuffers(_window);
	glfwPollEvents();
}
void Renderer::drawVertices(const RenderTarget & target) {
	// calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model;
	model = glm::translate(model, target.getModelPosition());
	if (target.getIfAutorotated() == true) {
		model = glm::rotate(model, glm::radians(target.getPitch()), target.getAxis());
		model = glm::rotate(model, glm::radians(target.getYaw()), glm::vec3(0.f, 1.f, 0.f));
	}
	else {
		model = glm::rotate(model, glm::radians(target.getRotation()), target.getAxis());
	}
	model = glm::scale(model, target.getScale());
	_shader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, target.getNumberOfVertices());
}
Renderer::~Renderer() {
	delete _shader;
	delete _camera;

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
}