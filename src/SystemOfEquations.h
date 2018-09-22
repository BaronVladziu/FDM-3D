//
// Created by baronvladziu on 21.09.18.
//

#ifndef VULKAN_FDM_SYSTEMOFEQUATIONS_H
#define VULKAN_FDM_SYSTEMOFEQUATIONS_H

#include "header.h"


class SystemOfEquations {

    int _numberOfVariables;
    float ** _matrix;

public:
    SystemOfEquations(int numberOfVariables);
    int getNumberOfVariables() const;
    float get(int x, int y) const;
    void set(int x, int y, float value);
    void setConstant(int y, float value);
    void solve() const;
    ~SystemOfEquations();

};


#endif //VULKAN_FDM_SYSTEMOFEQUATIONS_H
