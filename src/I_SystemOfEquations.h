//
// Created by baronvladziu on 26.10.18.
//

#ifndef VULKAN_FDM_I_SYSTEMOFEQUATIONS_H
#define VULKAN_FDM_I_SYSTEMOFEQUATIONS_H

#include "ComplexFloat.h"


class I_SystemOfEquations {

public:
    virtual int getNumberOfVariables() const = 0;
    virtual ComplexFloat get(int x, int y) const = 0;
    virtual ComplexFloat getConstant(int y) const = 0;
    virtual ComplexFloat getSolution(int y) const = 0;
    virtual void set(int x, int y, ComplexFloat value) = 0;
    virtual void setConstant(int y, ComplexFloat value) = 0;
    virtual void solve() = 0;
    virtual void print(int y) const = 0;
    
};


#endif //VULKAN_FDM_I_SYSTEMOFEQUATIONS_H
