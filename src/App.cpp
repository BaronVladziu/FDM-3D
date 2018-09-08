//
// Created by baronvladziu on 07.09.18.
//

#include "App.h"
#include "RenderVertex.h"

App::App() {
    RenderVertex a(-0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
    RenderVertex b(0.5f, -0.5f, 0.0f, 0.0f, 0.0f);
    RenderVertex c(0.5f, 0.5f, 0.0f, 0.0f, 1.0f);
    RenderVertex d(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f);
    RenderVertex e(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f);
    RenderVertex f(0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
    RenderVertex g(0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
    RenderVertex h(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f);

    RenderTriangle t1(a, b, c);
    RenderTriangle t2(c, d, a);
    RenderTriangle t3(e, f, g);
    RenderTriangle t4(g, h, e);

    std::vector<RenderTriangle> triangles = {t1, t2, t3, t4};

    _renderer.init(triangles);
}
void App::loop() {
    while (_renderer.isWindowOpen()) {
        _renderer.draw();
    }
}
App::~App() {
    _renderer.clean();
}