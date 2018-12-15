//
// Created by baronvladziu on 07.09.18.
//

#include "App.h"
#include "RenderVertex.h"
#include "Map.h"
#include "MapLoader.h"
#include "Solver.h"
#include "SolverConfiguration.h"


App::App() {
    srand(time(NULL));
    SolverConfiguration config("../maps/config.json");
    MapLoader mapLoader;
    Map map = mapLoader.loadMap("../maps/" + config.MODEL_NAME + "-w.json", "../maps/" + config.MODEL_NAME + "-s.json", "../maps/" + config.MODEL_NAME + "-r.json");



    Solver solver;
    std::list<RenderTriangle> solverTriangles;
    if (config.START_FREQUENCY < config.STOP_FREQUENCY) {
        solverTriangles = *solver.solveReceivers(map, config);
    }
    if (config.MAIN_FREQUENCY != 0.f) {
        solverTriangles = *solver.solveRoom(map, config);
    }

    std::list<RenderTriangle> triangles; //TODO: uses unnecessary memory
    triangles.insert(triangles.end(), map.getWallTriangles().begin(), map.getWallTriangles().end());
    triangles.insert(triangles.end(), map.getSpeakerTriangles().begin(), map.getSpeakerTriangles().end());

    _renderer.init(solverTriangles);
}
void App::loop() {
    while (_renderer.isWindowOpen()) {
        _renderer.draw();
    }
}
App::~App() {
    _renderer.clean();
}
