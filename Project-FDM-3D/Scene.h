#pragma once
#include "header.h"
#include "Tab.h"
#include "RenderRectangle.h"

class Scene
{
	RenderRectangle _rect1;
	RenderRectangle _rect2;
	std::list<Renderable *> _renderables;

public:
	Scene();
	const std::list<Renderable *> & getRenderables();
	void update();
	~Scene();
};