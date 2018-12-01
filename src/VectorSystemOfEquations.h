//
// Created by baronvladziu on 07.11.18.
//

#ifndef VULKAN_FDM_VECTORSYSTEMOFEQUATIONS_H
#define VULKAN_FDM_VECTORSYSTEMOFEQUATIONS_H


#include "FloatVector.h"

class VectorSystemOfEquations {

    const int _numberOfVariables;
    std::vector<FloatVector> _equations;
    FloatVector _values;
    FloatVector _solution;

public:
    explicit VectorSystemOfEquations(int numberOfVariables);
    int getNumberOfVariables() const;
    float get(int x, int y) const;
    float getConstant(int y) const;
    float getSolution(int y) const;
    void set(int x, int y, float value);
    void setConstant(int y, float value);
    void solve();
    void print(int y) const;

private:
    FloatVector calculateDiffVector(const FloatVector & solution) const;
    float calculateDiffVectorValue(const FloatVector & solution, int i) const;
    float calculateDiff(const FloatVector & solution) const;

};


#endif //VULKAN_FDM_VECTORSYSTEMOFEQUATIONS_H
