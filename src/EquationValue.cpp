//
// Created by baronvladziu on 27.09.18.
//

#include "EquationValue.h"

EquationValue::EquationValue(int variableID, const ComplexFloat & value)
    : _variableID(variableID), _value(value)
{}
int EquationValue::getVariableID() const {
    return _variableID;
}
const ComplexFloat & EquationValue::getValue() const {
    return _value;
}
void EquationValue::setValue(const ComplexFloat & value) {
    _value = value;
}
