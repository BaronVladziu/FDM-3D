//
// Created by baronvladziu on 07.09.18.
//

#include <stdexcept>
#include <iostream>
#include "App.h"

int main() {

    try {
        App app;
        app.loop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

