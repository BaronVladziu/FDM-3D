#include "Scene.h"

Scene::Scene()
{
	_map.loadModelFromFile("map");
}
const std::list<Renderable*> & Scene::getRenderables() {
	return _map.getRenderables();
}
void Scene::update() {}
Scene::~Scene() {}