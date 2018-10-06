//
// Created by baronvladziu on 07.09.18.
//

#include "App.h"
#include "RenderVertex.h"
#include "Map.h"
#include "MapLoader.h"
#include "Solver.h"


App::App() {
    MapLoader mapLoader;
    Map map = mapLoader.loadMap("../maps/room.json", "../maps/speakers.json");
    Solver solver;
    std::list<RenderTriangle> solverTriangles = solver.solveRoom(map, 50, Complex2RealType::IMAG, ScaleType::DECIBELS);

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