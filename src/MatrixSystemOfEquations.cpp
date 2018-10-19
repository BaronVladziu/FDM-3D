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

    std::cout << "\nCalculating constants:" << std::endl;
    const Matrix methodMatrix = _matrix.extractLower() + _matrix.extractUpper(); //TODO: Change to faster matrices
    const Matrix diagonalInverse = _matrix.extractDiagonalInverse();
    const Matrix fullMethodMatrix = diagonalInverse*methodMatrix;
    const Matrix constantMatrix = diagonalInverse*_values;

//    //Calculate largest eigenvalue
//    std::cout << "\nFinding largest eigenvalue:" << std::endl;
//    Matrix eigenvector(1, _numberOfVariables);
//    eigenvector.fillWith(ComplexFloat(sqrt(2.f), sqrt(2.f)));
//    ComplexFloat prevEigenvalue;
//    ComplexFloat eigenvalue = eigenvector.getMax();
    int i = 0;
//    do {
//        prevEigenvalue = eigenvalue;
//        //Transformation
//        eigenvector = fullMethodMatrix*eigenvector;
//        //Find max
//        eigenvalue = eigenvector.getMax();
//        //Normalization
//        eigenvector /= eigenvalue;
//        //Print
//        eigenvector.print();
//        std::cout << eigenvalue.toString() << std::endl;
//        i++;
//    } while (i < _MIN_ITERATION_NUMBER || !areNumbersSimilar(prevEigenvalue, eigenvalue));
//
//    //Optimal relaxation constant
//    ComplexFloat relaxationConstant = ComplexFloat(2, 0)/(ComplexFloat(1, 0)+((ComplexFloat(1,0)-eigenvalue*eigenvalue)).getRoot(2));


    //Solve equations
    std::cout << "\nSolving equations:" << std::endl;
    std::ofstream myfile;
    myfile.open ("results.txt");
    Matrix prevSolution = _solution;
    i = 0;
    do {
        prevSolution = _solution;

        //Iterate
        _solution = constantMatrix - fullMethodMatrix*_solution;
//        _solution = (_matrix.extractDiagonal())

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
bool MatrixSystemOfEquations::areSolutionsSimilar(const Matrix & v1, const Matrix & v2) const {
    for (int i = 0; i < _numberOfVariables; i++) {
        if (std::isnan(v1.get(0, i).real) || std::isnan(v1.get(0, i).imag) || std::isnan(v2.get(0, i).real) || std::isnan(v2.get(0, i).imag)) {
            std::cout << "ERROR: Unstable solution! Consider raising _NUMBER_OF_POINTS_PER_PERIOD value." << std::endl;
            return true;
        }
        ComplexFloat difference = v1.get(0, i) - v2.get(0, i);
        if (abs(difference.real) > _SIMILARITY_THRESHOLD || abs(difference.imag) > _SIMILARITY_THRESHOLD) {
            return false;
        }
    }
    return true;
}
bool MatrixSystemOfEquations::areNumbersSimilar(const ComplexFloat & x, const ComplexFloat & y) const {
    ComplexFloat difference = x - y;
    return (abs(difference.real) < _SIMILARITY_THRESHOLD && abs(difference.imag) < _SIMILARITY_THRESHOLD);
}
