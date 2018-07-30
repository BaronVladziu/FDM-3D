#pragma once
#include "header.h"
#include "Scene.h"
#include "Renderer.h"
#include "InputManager.h"

class App
{
	Scene _scene;
	Renderer _renderer;
	InputManager _inputManager;

public:
	App();
	void loop();
	~App();
};