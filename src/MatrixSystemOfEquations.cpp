//
// Created by baronvladziu on 04.10.18.
//

#include "MatrixSystemOfEquations.h"


//public:
MatrixSystemOfEquations::MatrixSystemOfEquations(int numberOfVariables)
    : _numberOfVariables(numberOfVariables), _matrix(numberOfVariables, numberOfVariables),
    _values(1, numberOfVariables), _solution(1, numberOfVariables)
{
    _solution.fillWith(ComplexFloat(0.f, 0.f));
    _matrix.fillWith(ComplexFloat(0.f, 0.f));
    _values.fillWith(ComplexFloat(0.f, 0.f));
}
int MatrixSystemOfEquations::getNumberOfVariables() const {
    return _numberOfVariables;
}
ComplexFloat MatrixSystemOfEquations::get(int x, int y) const {
    return _matrix.get(x, y);
}
ComplexFloat MatrixSystemOfEquations::getConstant(int y) const {
    return _values.get(0, y);
}
ComplexFloat MatrixSystemOfEquations::getSolution(int y) const {
    return _solution.get(0, y);
}
void MatrixSystemOfEquations::set(int x, int y, ComplexFloat value) {
    _matrix.set(x, y, value);
}
void MatrixSystemOfEquations::setConstant(int y, ComplexFloat value) {
    _values.set(0, y, value);
}
void MatrixSystemOfEquations::solve(int numberOfIterations) {
//    Matrix D = _matrix;
//    std::cout << "Matrix:" << D.getX() << " , " << D.getY() << std::endl;
//    D.print();

    std::ofstream myfile;
    myfile.open ("results.txt");
    for (int i = 0; i < numberOfIterations; i++) {
        iterate();
        std::cout << "Iteration: " << i << std::endl;
        std::cout << "Result: " << std::endl;
        _solution.print();

        //Print equations to file
        for (int j = 0; j < _numberOfVariables; j++) {
            myfile << _solution.get(0, j).toString() << '\t';
        }
        myfile << '\n';
    }
    myfile.close();
}
void MatrixSystemOfEquations::print(int y) const {
    for (int i = 0; i < _numberOfVariables; i++) {
        std::cout << "(" << _matrix.get(i, y).toString() << ")*x_" << i << " + ";
    }
    std::cout << " = " << _values.get(0, y).toString() << std::endl;
}

//private:
void MatrixSystemOfEquations::iterate() {
    _solution = _matrix.extractDiagonalInverse()*(_values - (_matrix.extractLower() + _matrix.extractUpper())*_solution);
}
