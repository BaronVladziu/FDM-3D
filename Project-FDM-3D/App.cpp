#include "App.h"

App::App() {}
void App::loop() {
	while (_renderer.isWindowOpen()) {
		_scene.update();
		_renderer.draw(_scene.getRenderables());
	}
}
App::~App() {}