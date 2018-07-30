#include "InputManager.h"

Renderer * InputManager::_renderer = nullptr;
Scene * InputManager::_scene = nullptr;

// glfw: whenever the mouse moves, this callback is called
void InputManager::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	_renderer->turnCamera(xpos, ypos);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void InputManager::scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
	_renderer->zoomCamera(yoffset);
}
void InputManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	switch (mods) {
	case 0:
		processKeyEventWithoutModifiers(key, action);
		break;
	case 1:
		processKeyEventWithShift(key, action);
		break;
	case 2:
		processKeyEventWithCtrl(key, action);
		break;
	case 3:
		processKeyEventWithCtrlShift(key, action);
		break;
	case 4:
		processKeyEventWithAlt(key, action);
		break;
	case 5:
		processKeyEventWithShiftAlt(key, action);
		break;
	case 6:
		processKeyEventWithCtrlAlt(key, action);
		break;
	case 7:
		processKeyEventWithCtrlShiftAlt(key, action);
		break;
	}
}

void InputManager::processKeyEventWithoutModifiers(int key, int action) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(_renderer->getWindow(), true); //TODO
		//_scene->orderAction(E_InputAction::ExitApp);
	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::DeleteObject);
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::MarkObject);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::TargetNext);
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::TargetPrevious);
}
void InputManager::processKeyEventWithCtrl(int key, int action) {
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::SaveFiles);
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::LoadFiles);
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::Undo);
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::Redo);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::MarkAllObjects);
}
void InputManager::processKeyEventWithShift(int key, int action) {}
void InputManager::processKeyEventWithAlt(int key, int action) {
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::SetXAxisActive);
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::SetYAxisActive);
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::SetZAxisActive);
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::SetPointMode);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::SetPlaneMode);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::SetSpeakerMode);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::AddObject);
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		_scene->orderAction(E_InputAction::DeleteObject);
}
void InputManager::processKeyEventWithCtrlShift(int key, int action) {}
void InputManager::processKeyEventWithCtrlAlt(int key, int action) {}
void InputManager::processKeyEventWithShiftAlt(int key, int action) {}
void InputManager::processKeyEventWithCtrlShiftAlt(int key, int action) {}

void InputManager::processKeyInputWithoutModifiers() {
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Front, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Left, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Back, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Right, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Up, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		_scene->orderAction(E_InputAction::MoveCloser);
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		_scene->orderAction(E_InputAction::MoveFurther);
}
void InputManager::processKeyInputWithCtrl() {}
void InputManager::processKeyInputWithShift() {
	_renderer->moveCamera(E_Direction6::Down, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Front, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Left, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Back, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Right, _renderer->getDeltaTime());
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		_renderer->moveCamera(E_Direction6::Up, _renderer->getDeltaTime());
}
void InputManager::processKeyInputWithAlt() {}
void InputManager::processKeyInputWithCtrlShift() {}
void InputManager::processKeyInputWithCtrlAlt() {}
void InputManager::processKeyInputWithShiftAlt() {}
void InputManager::processKeyInputWithCtrlShiftAlt() {}

InputManager::InputManager(Scene * scene, Renderer * renderer)
{
	_scene = scene;
	_renderer = renderer;
	glfwSetCursorPosCallback(_renderer->getWindow(), InputManager::mouse_callback);
	glfwSetScrollCallback(_renderer->getWindow(), InputManager::scroll_callback);
	glfwSetKeyCallback(_renderer->getWindow(), key_callback);
}
void InputManager::processInput(float deltaTime) {
	if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE &&
		glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_ALT) == GLFW_RELEASE) {
		if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE &&
			glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE) {
			if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
				glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE) {
				processKeyInputWithoutModifiers();
			}
			else if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
				glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				processKeyInputWithShift();
			}
		}
		else if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
			glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
				glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE) {
				processKeyInputWithCtrl();
			}
			else if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
				glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				processKeyInputWithCtrlShift();
			}
		}
	}
	else if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
		glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
		if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE &&
			glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE) {
			if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
				glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE) {
				processKeyInputWithAlt();
			}
			else if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
				glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				processKeyInputWithShiftAlt();
			}
		}
		else if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
			glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
				glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE) {
				processKeyInputWithCtrlAlt();
			}
			else if (glfwGetKey(_renderer->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
				glfwGetKey(_renderer->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				processKeyInputWithCtrlShiftAlt();
			}
		}
	}
}
InputManager::~InputManager()
{}