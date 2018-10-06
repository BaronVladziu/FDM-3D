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
void MatrixSystemOfEquations::solve() {
//    Matrix D = _matrix;
//    std::cout << "Matrix:" << D.getX() << " , " << D.getY() << std::endl;
//    D.print();

    std::ofstream myfile;
    myfile.open ("results.txt");
    Matrix prevSolution = _solution;
    int i = 0;
    do {
        prevSolution = _solution;
        iterate();
        std::cout << "Iteration: " << i << std::endl;
        std::cout << "Result: " << std::endl;
        _solution.print();

        //Print equations to file
        for (int j = 0; j < _numberOfVariables; j++) {
            myfile << _solution.get(0, j).toString() << '\t';
        }
        myfile << '\n';
        i++;
    } while (i < _MIN_ITERATION_NUMBER || !areSolutionsSimilar(prevSolution,  _solution));
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
bool MatrixSystemOfEquations::areSolutionsSimilar(const Matrix & v1, const Matrix & v2) const {
    for (int i = 0; i < _numberOfVariables; i++) {
        if (std::isnan(v1.get(0, i).real) || std::isnan(v1.get(0, i).imag) || std::isnan(v2.get(0, i).real) || std::isnan(v2.get(0, i).imag)) {
            std::cout << "ERROR: Unstable solution! Consider raising _NUMBER_OF_POINTS_PER_PERIOD value." << std::endl;
            return true;
        }
        ComplexFloat difference = v1.get(0, i) - v2.get(0, i);
        if (difference.real > _SIMILARITY_THRESHOLD || difference.imag > _SIMILARITY_THRESHOLD) {
            return false;
        }
    }
    return true;
}
