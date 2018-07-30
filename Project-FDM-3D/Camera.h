#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "E_Direction6.h"

class Camera
{
	glm::vec3 _cameraPos;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;
	bool _firstMouse;
	float _yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float _pitch;
	float _lastX;
	float _lastY;
	float _fov;
	float _minFov;
	float _maxFov;

public:
	Camera(GLFWwindow * window);
	void move(E_Direction6 direction, float deltaTime);
	void turn(double xpos, double ypos);
	void zoom(double offset);
	const glm::vec3 & getPos() const;
	const glm::vec3 & getFront() const;
	const glm::vec3 & getUp() const;
	float getFov() const;
	void setFov(float fov);
	~Camera();
};