//
// Created by baronvladziu on 21.09.18.
//

#include "SystemOfEquations.h"


SystemOfEquations::SystemOfEquations(int numberOfVariables)
    : _numberOfVariables(numberOfVariables)
{
    _matrix = new float * [_numberOfVariables + 1];
    for (int i = 0; i <= _numberOfVariables; i++) {
        _matrix[i] = new float [_numberOfVariables];
        for (int j = 0; j <= _numberOfVariables; j++) {
            _matrix[i][j] = 0.f;
        }
    }
}
int SystemOfEquations::getNumberOfVariables() const {
    return _numberOfVariables;
}
float SystemOfEquations::get(int x, int y) const {
    return _matrix[x][y];
}
void SystemOfEquations::set(int x, int y, float value) {
    _matrix[x][y] = value;
}
void SystemOfEquations::setConstant(int y, float value) {
    _matrix[_numberOfVariables][y] = value;
}
void SystemOfEquations::solve() const {
    std::cout << "TODO: Implement it!" << std::endl; //TODO: Implement it!
}
SystemOfEquations::~SystemOfEquations() {
    for (int i = 0; i <= _numberOfVariables; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}
