//
// Created by baronvladziu on 04.10.18.
//

#ifndef VULKAN_FDM_MATRIXSYSTEMOFEQUATIONS_H
#define VULKAN_FDM_MATRIXSYSTEMOFEQUATIONS_H

#include "header.h"
#include "MapMatrix.h"
#include "I_SystemOfEquations.h"


class MatrixSystemOfEquations
        : public I_SystemOfEquations {

    static constexpr float _SIMILARITY_THRESHOLD = 0.000001f;
    static constexpr int _MIN_ITERATION_NUMBER = 10;

    const int _numberOfVariables;
    MapMatrix _matrix;
    MapMatrix _values;
    MapMatrix _solution;

public:
    explicit MatrixSystemOfEquations(int numberOfVariables);
    int getNumberOfVariables() const;
    ComplexFloat get(int x, int y) const;
    ComplexFloat getConstant(int y) const;
    ComplexFloat getSolution(int y) const;
    void set(int x, int y, ComplexFloat value);
    void setConstant(int y, ComplexFloat value);
    void solve();
    void print(int y) const;

private:
    bool areSolutionsSimilar(const MapMatrix & v1, const MapMatrix & v2) const;
    bool areNumbersSimilar(const ComplexFloat & x, const ComplexFloat & y) const;

};


#endif //VULKAN_FDM_MATRIXSYSTEMOFEQUATIONS_H
