#pragma once
#include "header.h"
#include <glad/glad.h>
#include "Scene.h"
#include "Renderer.h"

class InputManager
{
	static Scene * _scene;
	static Renderer * _renderer;

	static void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	
	static void processKeyEventWithoutModifiers(int key, int action);
	static void processKeyEventWithCtrl(int key, int action);
	static void processKeyEventWithShift(int key, int action);
	static void processKeyEventWithAlt(int key, int action);
	static void processKeyEventWithCtrlShift(int key, int action);
	static void processKeyEventWithCtrlAlt(int key, int action);
	static void processKeyEventWithShiftAlt(int key, int action);
	static void processKeyEventWithCtrlShiftAlt(int key, int action);

	void processKeyInputWithoutModifiers();
	void processKeyInputWithCtrl();
	void processKeyInputWithShift();
	void processKeyInputWithAlt();
	void processKeyInputWithCtrlShift();
	void processKeyInputWithCtrlAlt();
	void processKeyInputWithShiftAlt();
	void processKeyInputWithCtrlShiftAlt();

public:
	InputManager(Scene * scene, Renderer * renderer);
	void processInput(float deltaTime);
	~InputManager();
};