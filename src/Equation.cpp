//
// Created by baronvladziu on 27.09.18.
//

#include "Equation.h"


Equation::Equation()
    : _eqID(-1), _value(0.f, 0.f)
{}
void Equation::setID(int eqID) {
    _eqID = eqID;
}
int Equation::getID() const {
    return _eqID;
}
void Equation::addVariable(EquationValue equationValue) {
    _variables.emplace_back(equationValue);
}
void Equation::removeVariable(int variableID, const ComplexFloat & variableValue) {
    std::list<EquationValue>::iterator it = _variables.begin();
    while (it != _variables.end()) {
        if (it->getVariableID() == variableID) {
            _value -= it->getValue() * variableValue;
            it = _variables.erase(it);
        } else {
            it++;
        }
    }
}
void Equation::removeVariable(const EquationValue & variable) {
    removeVariable(variable.getVariableID(), variable.getValue());
}
unsigned long Equation::getNumberOfVariables() const {
    return _variables.size();
}
int Equation::getEquationID() const {
    return _eqID;
}
ComplexFloat Equation::getVariable(int variableID) const {
    for (const EquationValue & equationValue : _variables) {
        if (equationValue.getVariableID() == variableID) {
            return equationValue.getValue();
        }
    }
    return ComplexFloat(0.f, 0.f);
}
const std::list<EquationValue> & Equation::getVariables() const {
    return _variables;
}
EquationValue Equation::getValue() const {
    return EquationValue(_variables.front().getVariableID(), _value);
}
void Equation::setValue(const ComplexFloat & value) {
    _value = value;
}
void Equation::print() const {
    for (const EquationValue & eqVal : _variables) {
        std::cout << "(" << eqVal.getValue().toString() << ")*x_" << eqVal.getVariableID() << " + ";
    }
    std::cout << " = " << _value.toString() << std::endl;
}
