#pragma once
#include "header.h"
#include "Tab.h"
#include "Model.h"

class Scene
{
	Model _map;

public:
	Scene();
	const std::list<Renderable*> & getRenderables();
	void update();
	~Scene();
};