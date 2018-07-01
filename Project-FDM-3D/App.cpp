#include "App.h"

App::App() {
}
void App::loop() {
	while (_renderer.isWindowOpen()) {
		_renderer.update();
	}
}
App::~App() {}