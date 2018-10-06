//
// Created by baronvladziu on 27.09.18.
//

#ifndef VULKAN_FDM_EQUATION_H
#define VULKAN_FDM_EQUATION_H

#include "header.h"
#include "EquationValue.h"


class Equation {

    int _eqID;
    std::list<EquationValue> _variables;
    ComplexFloat _value;

public:
    Equation();
    void setID(int eqID);
    int getID() const;
    void addVariable(EquationValue equationValue);
    void removeVariable(int variableID, const ComplexFloat & variableValue);
    void removeVariable(const EquationValue & variable);
    unsigned long getNumberOfVariables() const;
    int getEquationID() const;
    ComplexFloat getVariable(int variableID) const;
    const std::list<EquationValue> & getVariables() const;
    EquationValue getValue() const;
    void setValue(const ComplexFloat & value);
    void print() const;

};


#endif //VULKAN_FDM_EQUATION_H
