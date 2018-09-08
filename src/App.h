//
// Created by baronvladziu on 07.09.18.
//
#pragma once
#include "header.h"

#include "Renderer.h"

class App {
    Renderer _renderer;

public:
    App();
    void loop();
    ~App();

};
