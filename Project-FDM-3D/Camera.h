#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;
	static bool firstMouse;
	static float yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	static float pitch;
	static float lastX;
	static float lastY;
	static float fov;

	static void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

public:
	Camera(GLFWwindow * window);
	static void processInput(GLFWwindow * window, float deltaTime);
	const glm::vec3 & getPos() const;
	const glm::vec3 & getFront() const;
	const glm::vec3 & getUp() const;
	float getFov() const;
	~Camera();
};