#include "App.h"

App::App()
	: _inputManager(&_scene, &_renderer)
{}
void App::loop() {
	while (_renderer.isWindowOpen()) {
		_renderer.update();
		_scene.update(_renderer.getDeltaTime());
		_inputManager.processInput(_renderer.getDeltaTime());
		_renderer.draw(_scene.getModels());
	}
}
App::~App() {}