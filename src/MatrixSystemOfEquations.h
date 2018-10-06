//
// Created by baronvladziu on 04.10.18.
//

#ifndef VULKAN_FDM_MATRIXSYSTEMOFEQUATIONS_H
#define VULKAN_FDM_MATRIXSYSTEMOFEQUATIONS_H

#include "header.h"
#include "Matrix.h"


class MatrixSystemOfEquations {

    const int _numberOfVariables;
    Matrix _matrix;
    Matrix _values;
    Matrix _solution;

public:
    explicit MatrixSystemOfEquations(int numberOfVariables);
    int getNumberOfVariables() const;
    ComplexFloat get(int x, int y) const;
    ComplexFloat getConstant(int y) const;
    ComplexFloat getSolution(int y) const;
    void set(int x, int y, ComplexFloat value);
    void setConstant(int y, ComplexFloat value);
    void solve(int numberOfIterations);
    void print(int y) const;

private:
    void iterate();

};


#endif //VULKAN_FDM_MATRIXSYSTEMOFEQUATIONS_H
