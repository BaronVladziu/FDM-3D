//
// Created by baronvladziu on 21.09.18.
//

#include "SystemOfEquations.h"


//public:
SystemOfEquations::SystemOfEquations(int numberOfVariables)
    : _numberOfVariables(numberOfVariables)
{
    _equations = new Equation[_numberOfVariables];
    for (int i = 0; i < _numberOfVariables; i++) {
        _equations[i].setID(i);
    }
}
int SystemOfEquations::getNumberOfVariables() const {
    return _numberOfVariables;
}
ComplexFloat SystemOfEquations::get(int x, int y) const {
    return _equations[y].getVariable(x);
}
ComplexFloat SystemOfEquations::getConstant(int y) const {
    return _equations[y].getValue().getValue();
}
void SystemOfEquations::set(int x, int y, ComplexFloat value) {
    assert(x >= 0);
    assert(x < _numberOfVariables);
    assert(y >= 0);
    assert(y < _numberOfVariables);
    _equations[y].addVariable(EquationValue(x, value));
}
void SystemOfEquations::setConstant(int y, ComplexFloat value) {
    _equations[y].setValue(value);
}
void SystemOfEquations::solve() {
    std::cout << "Solving..." << std::endl;

    std::cout << "Equation reduction phase..." << std::endl;
    //Split to solved and unsolved equations
    std::list<Equation *> solvedEquations;
    std::list<Equation *> unsolvedEquations;
    for (int actEq = 0; actEq < _numberOfVariables; actEq++) {
        std::cout << "eqSize: " << _equations[actEq].getNumberOfVariables() << std::endl;
        if (_equations[actEq].getNumberOfVariables() == 1) {
            solvedEquations.emplace_back(&_equations[actEq]);
            std::cout << "ID: " << _equations[actEq].getValue().getVariableID() << "\t Val: " << _equations[actEq].getValue().getValue().toString() << std::endl;
        } else {
            unsolvedEquations.emplace_back(&_equations[actEq]);
        }
    }
    //Solve trivial equations ( O(n²) )
    while (!solvedEquations.empty()) {
        Equation * actSolvedEq = *solvedEquations.begin();
        solvedEquations.pop_front();
        std::list<Equation *>::iterator actUnsolvedEq = unsolvedEquations.begin();
        while (actUnsolvedEq != unsolvedEquations.end()) {
            (*actUnsolvedEq)->removeVariable(actSolvedEq->getValue());
            if ((*actUnsolvedEq)->getNumberOfVariables() == 1) {
                solvedEquations.emplace_back(*actUnsolvedEq);
                std::cout << "ID: " << (*actUnsolvedEq)->getValue().getVariableID() << "\t Val: " << (*actUnsolvedEq)->getValue().getValue().toString() << std::endl;
                actUnsolvedEq = unsolvedEquations.erase(actUnsolvedEq);
            } else {
                actUnsolvedEq++;
            }
        }
    }
    std::cout << "Solved " << _numberOfVariables - unsolvedEquations.size() << " of " << _numberOfVariables << " variables" << std::endl;

    std::cout << "Gauss method phase..." << std::endl;
    int newNumberOfValues = int(unsolvedEquations.size());
    int * idToVariableTable = new int[newNumberOfValues];
    int * variableToIDTable = new int[_numberOfVariables];
    for (int i = 0; i < _numberOfVariables; i++) {
        variableToIDTable[i] = -1;
    }

    int i = 0;
    std::list<Equation *>::iterator eq = unsolvedEquations.begin();
    while (eq != unsolvedEquations.end()) {
        idToVariableTable[i] = (*eq)->getID();
        variableToIDTable[(*eq)->getID()] = i;
        eq++;
        i++;
    }
    Matrix matrix(newNumberOfValues + 1, newNumberOfValues);
    matrix.fillWith(ComplexFloat(0.f, 0.f));
    i = 0;
    eq = unsolvedEquations.begin();
    while (eq != unsolvedEquations.end()) {
        assert(!(*eq)->getVariables().empty());
        for (const EquationValue & eqVal : (*eq)->getVariables()) {
            matrix.set(i, variableToIDTable[eqVal.getVariableID()], eqVal.getValue());
        }
        matrix.set(newNumberOfValues, i, (*eq)->getValue().getValue());
        eq++;
        i++;
    }
    matrix.removeZerosFromDiagonal();
    matrix.solve();

    std::cout << "Matrix:" << std::endl;
    matrix.print();
    delete[] idToVariableTable;
    delete[] variableToIDTable;



//    std::ofstream myfile;
//    myfile.open ("results.txt");
//    for (int i = 0; i < numberOfIterations; i++) {
//        iterate();
//        std::cout << "Iteration: " << i << std::endl;
//        std::cout << "Result: " << std::endl;
//        _solution.print();
//
//        //Print equations to file
//        for (int j = 0; j < _numberOfVariables; j++) {
//            myfile << _solution.get(0, j) << '\t';
//        }
//        myfile << '\n';
//
//    }
//    myfile.close();
}
void SystemOfEquations::print(int y) const {
    _equations[y].print();
}
SystemOfEquations::~SystemOfEquations() {
    delete[] _equations;
}
