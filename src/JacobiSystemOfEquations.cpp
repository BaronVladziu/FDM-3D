//
// Created by baronvladziu on 29.11.18.
//

#include "JacobiSystemOfEquations.h"
#include "JacobiMatrix.h"

JacobiSystemOfEquations::JacobiSystemOfEquations(int numberOfVariables)
        : _numberOfVariables(numberOfVariables), _matrix(numberOfVariables, numberOfVariables),
          _values(1, numberOfVariables), _solution(1, numberOfVariables)
{
    _solution.fillWithZeros();
    _matrix.fillWithZeros();
    _values.fillWithZeros();
}
int JacobiSystemOfEquations::getNumberOfVariables() const {
    return _numberOfVariables;
}
float JacobiSystemOfEquations::get(int x, int y) const {
    return _matrix.get(x, y);
}
float JacobiSystemOfEquations::getConstant(int y) const {
    return _values.get(0, y);
}
float JacobiSystemOfEquations::getSolution(int y) const {
    return _solution.get(0, y);
}
void JacobiSystemOfEquations::set(int x, int y, float value) {
    _matrix.set(x, y, value);
}
void JacobiSystemOfEquations::setConstant(int y, float value) {
    _values.set(0, y, value);
}
void JacobiSystemOfEquations::solve() {
    //--- Jacobi Method ---//
//    std::cout << "\nCalculating constants:" << std::endl;
//    const JacobiMatrix diagonalInverse = _matrix.extractDiagonalInverse();
//    const JacobiMatrix methodMatrix = diagonalInverse*(_matrix.extractLower() + _matrix.extractUpper());
//    const JacobiMatrix constantMatrix = diagonalInverse*_values;
//
//    //Solve equations
//    std::cout << "\nSolving equations:" << std::endl;
//    std::ofstream myfile;
//    myfile.open ("results.txt");
//    JacobiMatrix prevSolution(1, _numberOfVariables);
//    prevSolution.randomize();
//    std::cout << "Iteration: 0" << std::endl;
//    std::cout << "Result: " << std::endl;
//    _solution.print();
//    int i = 1;
//    do {
//        prevSolution = _solution;
//
//        //Iterate
//        std::cout << "Iteration: " << i << std::endl;
//        _solution =  methodMatrix*_solution - constantMatrix;
//        std::cout << "Result: " << std::endl;
//        _solution.print();
////
////        //Print equations to file
////        for (int j = 0; j < _numberOfVariables; j++) {
////            myfile << _solution.get(0, j).toString() << '\t';
////        }
////        myfile << '\n';
//        i++;
//    } while (i < _MIN_ITERATION_NUMBER || !areSolutionsSimilar(prevSolution,  _solution, _SIMILARITY_THRESHOLD));
//    myfile.close();


    //--- Gauss method ---//
    std::cout << "Creating matrix:" << std::endl;
    Matrix<float> equations(_numberOfVariables + 1, _numberOfVariables);
    equations.fillWithZeros();
    for (int j = 0; j < _numberOfVariables; j++) {
        for (auto eq : _matrix.getValues(j)) {
            equations.set(eq.first, j, eq.second);
        }
        equations.set(_numberOfVariables, j, _values.get(0, j));
    }
    std::cout << "Solving matrix:" << std::endl;
    equations.solve();
    std::cout << "Saving results:" << std::endl;
    for (int j = 0; j < _numberOfVariables; j++) {
        _solution.set(0, j, equations.get(_numberOfVariables, j));
    }
}
void JacobiSystemOfEquations::print(int y) const {
    for (int i = 0; i < _numberOfVariables; i++) {
        if (_matrix.get(i, y) != 0.f) {
            std::cout << "(" << _matrix.get(i, y) << ")*x_" << i << " + ";
        }
    }
    std::cout << " = " << _values.get(0, y) << std::endl;
}

//private:
bool JacobiSystemOfEquations::areSolutionsSimilar(const JacobiMatrix & v1, const JacobiMatrix & v2, float similarityThreshold) const {
    for (int i = 0; i < _numberOfVariables; i++) {
        if (std::isnan(v1.get(0, i)) || std::isnan(v1.get(0, i)) ||
            std::isnan(v2.get(0, i)) || std::isnan(v2.get(0, i)) ||
            std::isinf(v1.get(0, i)) || std::isinf(v1.get(0, i)) ||
            std::isinf(v2.get(0, i)) || std::isinf(v2.get(0, i))) {
            std::cout << "ERROR: Unstable solution! Consider raising _NUMBER_OF_POINTS_PER_PERIOD value." << std::endl;
            return true;
        }
        float difference = v1.get(0, i) - v2.get(0, i);
        if (abs(difference) > similarityThreshold) {
            return false;
        }
    }
    return true;
}
bool JacobiSystemOfEquations::areNumbersSimilar(float x, float y, float similarityThreshold) const {
    float difference = x - y;
    return (abs(difference) < similarityThreshold);
}
