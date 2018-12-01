//
// Created by baronvladziu on 29.11.18.
//

#ifndef VULKAN_FDM_JACOBYSYSTEMOFEQUATIONS_H
#define VULKAN_FDM_JACOBYSYSTEMOFEQUATIONS_H


#include "Matrix.h"
#include "JacobiMatrix.h"

class JacobiSystemOfEquations {

    static constexpr float _SIMILARITY_THRESHOLD = 0.0001f;
    static constexpr int _MIN_ITERATION_NUMBER = 10;

    const int _numberOfVariables;
    JacobiMatrix _matrix;
    JacobiMatrix _values;
    JacobiMatrix _solution;

public:
    explicit JacobiSystemOfEquations(int numberOfVariables);
    int getNumberOfVariables() const;
    float get(int x, int y) const;
    float getConstant(int y) const;
    float getSolution(int y) const;
    void set(int x, int y, float value);
    void setConstant(int y, float value);
    void solve();
    void print(int y) const;

private:
    bool areSolutionsSimilar(const JacobiMatrix & v1, const JacobiMatrix & v2, float similarityThreshold) const;
    bool areNumbersSimilar(float x, float y, float similarityThreshold) const;

};


#endif //VULKAN_FDM_JACOBYSYSTEMOFEQUATIONS_H
