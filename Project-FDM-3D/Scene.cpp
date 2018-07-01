#include "Scene.h"

Scene::Scene()
	: _rect1(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.5f, 0.5f, -0.5f), Vector3f(-0.5f, 0.5f, -0.5f)),
	_rect2(Vector3f(-1.5f, -1.5f, -1.5f), Vector3f(1.5f, -1.5f, -1.5f), Vector3f(1.5f, 1.5f, -1.5f), Vector3f(-1.5f, 1.5f, -2.5f))
{
	_renderables.push_back(&_rect1);
	_renderables.push_back(&_rect2);
}
const std::list<Renderable*> & Scene::getRenderables() {
	return _renderables;
}
void Scene::update() {}
Scene::~Scene() {}