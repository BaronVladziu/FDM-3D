//
// Created by baronvladziu on 07.09.18.
//

#include "App.h"
#include "RenderVertex.h"
#include "Map.h"
#include "MapLoader.h"


App::App() {
    MapLoader mapLoader;
    Map map = mapLoader.loadMap("../maps/testmap.json");

    _renderer.init(map.getRenderTriangles());
}
void App::loop() {
    while (_renderer.isWindowOpen()) {
        _renderer.draw();
    }
}
App::~App() {
    _renderer.clean();
}