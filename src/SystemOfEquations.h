//
// Created by baronvladziu on 21.09.18.
//

#ifndef VULKAN_FDM_SYSTEMOFEQUATIONS_H
#define VULKAN_FDM_SYSTEMOFEQUATIONS_H

#include "header.h"
#include "Equation.h"
#include "Matrix.h"
#include "I_SystemOfEquations.h"


class SystemOfEquations
        : public I_SystemOfEquations {

    const int _numberOfVariables;
    Equation * _equations;

public:
    explicit SystemOfEquations(int numberOfVariables);
    int getNumberOfVariables() const;
    ComplexFloat get(int x, int y) const;
    ComplexFloat getConstant(int y) const;
    ComplexFloat getSolution(int y) const;
    void set(int x, int y, const ComplexFloat & value);
    void setConstant(int y, const ComplexFloat & value);
    void solve();
    void print(int y) const;
    ~SystemOfEquations();

};


#endif //VULKAN_FDM_SYSTEMOFEQUATIONS_H
