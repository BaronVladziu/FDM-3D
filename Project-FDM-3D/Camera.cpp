#include "Camera.h"

// glfw: whenever the mouse moves, this callback is called
void Camera::turn(double xpos, double ypos) {
	if (_firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		_firstMouse = false;
	}

	float xoffset = xpos - _lastX;
	float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top
	_lastX = xpos;
	_lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_cameraFront = glm::normalize(front);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void Camera::zoom(double offset) {
	if (_fov >= _minFov && _fov <= _maxFov)
		_fov -= offset * 5;
	if (_fov <= _minFov)
		_fov = _minFov;
	if (_fov >= _maxFov)
		_fov = _maxFov;
}

Camera::Camera(GLFWwindow * window)
	: _minFov(5.f), _maxFov(80)
{
	_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	_firstMouse = true;
	_yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	_pitch = 0.0f;
	_lastX = 800.0f / 2.0;
	_lastY = 600.0 / 2.0;
	_fov = 45.0f;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void Camera::move(E_Direction6 direction, float deltaTime) {
	float cameraSpeed = 2.5 * deltaTime;
	switch (direction) {
	case E_Direction6::Front:
		_cameraPos += cameraSpeed * _cameraFront;
		break;
	case E_Direction6::Right:
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
		break;
	case E_Direction6::Back:
		_cameraPos -= cameraSpeed * _cameraFront;
		break;
	case E_Direction6::Left:
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
		break;
	case E_Direction6::Up:
		_cameraPos += cameraSpeed * _cameraUp;
		break;
	case E_Direction6::Down:
		_cameraPos -= cameraSpeed * _cameraUp;
		break;
	}
}
const glm::vec3 & Camera::getPos() const {
	return _cameraPos;
}
const glm::vec3 & Camera::getFront() const {
	return _cameraFront;
}
const glm::vec3 & Camera::getUp() const {
	return _cameraUp;
}
float Camera::getFov() const {
	return _fov;
}
void Camera::setFov(float fov) {
	_fov = fov;
	_maxFov = fov;
}
Camera::~Camera() {}