#pragma once
#include "header.h"
#include "Scene.h"
#include "Renderer.h"

class App
{
	Scene _scene;
	Renderer _renderer;

public:
	App();
	void loop();
	~App();
};