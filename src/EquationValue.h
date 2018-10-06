//
// Created by baronvladziu on 27.09.18.
//

#ifndef VULKAN_FDM_EQUATIONVALUE_H
#define VULKAN_FDM_EQUATIONVALUE_H

#include "header.h"
#include "ComplexFloat.h"


class EquationValue {

    int _variableID;
    ComplexFloat _value;

public:
    EquationValue(int variableID, const ComplexFloat & value);
    int getVariableID() const;
    const ComplexFloat & getValue() const;
    void setValue(const ComplexFloat & value);

};


#endif //VULKAN_FDM_EQUATIONVALUE_H
