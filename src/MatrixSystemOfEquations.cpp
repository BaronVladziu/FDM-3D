//
// Created by baronvladziu on 04.10.18.
//

#include "MatrixSystemOfEquations.h"
#include "Matrix.h"


//public:
MatrixSystemOfEquations::MatrixSystemOfEquations(int numberOfVariables)
    : _numberOfVariables(numberOfVariables), _matrix(numberOfVariables, numberOfVariables),
    _values(1, numberOfVariables), _solution(1, numberOfVariables)
{
    _solution.fillWithZeros();
    _matrix.fillWithZeros();
    _values.fillWithZeros();
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
void MatrixSystemOfEquations::set(int x, int y, const ComplexFloat & value) {
    _matrix.set(x, y, value);
}
void MatrixSystemOfEquations::setConstant(int y, const ComplexFloat & value) {
    _values.set(0, y, value);
}
void MatrixSystemOfEquations::solve() {
//    Matrix D = _matrix;
//    std::cout << "Matrix:" << D.getX() << " , " << D.getY() << std::endl;
//    D.print();

//    std::cout << "\nCalculating constants:" << std::endl;
//    const MapMatrix diagonalInverse = _matrix.extractDiagonalInverse();
//    const MapMatrix methodMatrix = diagonalInverse*(_matrix.extractLower() + _matrix.extractUpper());
//    const MapMatrix constantMatrix = diagonalInverse*_values;

//    //Compute method matrix (inverted one)
//    std::cout << "\nComputing method matrix:" << std::endl;
//    MapMatrix uninvertedMethodMatrix = _matrix.extractDiagonal() + _matrix.extractLower();
//    MapMatrix identityMatrix(_numberOfVariables, _numberOfVariables);
//    for (int i = 0; i < _numberOfVariables; i++) {
//        identityMatrix.set(i, i, ComplexFloat(1.f,0.f));
//    }
//    MapMatrix methodMatrix = identityMatrix;
////    MapMatrix prevMethodMatrix(0,0);
    int i = 0;
//    do {
//        std::cout << "Iteration: " << i << std::endl;
////        prevMethodMatrix = methodMatrix;
//        MapMatrix av = uninvertedMethodMatrix*methodMatrix;
//        methodMatrix = methodMatrix*ComplexFloat(0.5f,0.f)*((identityMatrix*ComplexFloat(9.f,0.f)) -
//                (av*(identityMatrix*ComplexFloat(16.f,0.f) -
//                        (av*(identityMatrix*ComplexFloat(14.f,0.f) -
//                                (av*(identityMatrix*ComplexFloat(6.f,0.f) - av)))))));
//        i++;
//    } while (i < 1);
//    MapMatrix constantMatrix = methodMatrix*_values;
//    methodMatrix = methodMatrix*_matrix.extractUpper();

//    //Calculate largest eigenvalue
//    std::cout << "\nFinding largest eigenvalue:" << std::endl;
//    MapMatrix eigenvector(1, _numberOfVariables);
//    for (int i = 0; i < _numberOfVariables; i++) {
//        eigenvector.set(0, i, ComplexFloat(sqrt(2.f), sqrt(2.f)));
//    }
//    ComplexFloat prevEigenvalue;
//    ComplexFloat eigenvalue = eigenvector.getMax();
//    i = 0;
//    do {
//        std::cout << "Iteration: " << i << std::endl;
//        prevEigenvalue = eigenvalue;
//        //Transformation
//        eigenvector = methodMatrix*eigenvector;
//        //Find max
//        eigenvalue = eigenvector.getMax();
//        //Normalization
//        eigenvector /= eigenvalue;
//        //Print
////        eigenvector.print();
//        std::cout << eigenvalue.toString() << std::endl;
//        i++;
//    } while (i < _MIN_ITERATION_NUMBER || !areNumbersSimilar(prevEigenvalue, eigenvalue, 0.001f));
//
//    if (abs(eigenvalue.real) > 1.f || abs(eigenvalue.imag) > 1.f) {
//        std::cout << "Largest eigenvalue > 1! Solution would be unstable!" << std::endl;
//        return;
//    }

//    //Optimal relaxation constant
//    ComplexFloat relaxationConstant = ComplexFloat(2, 0)/(ComplexFloat(1, 0)+((ComplexFloat(1,0)-eigenvalue*eigenvalue)).getRoot(2));
//    std::cout << "\nOptimal relaxation factor: " << eigenvalue.toString() << std::endl;


    //Solve equations
//    std::cout << "\nSolving equations:" << std::endl;
//    std::ofstream myfile;
//    myfile.open ("results.txt");
//    MapMatrix prevSolution = _solution;
//    i = 0;
//    do {
//        prevSolution = _solution;
//
//        //Iterate
//        std::cout << "Iteration: " << i << std::endl;
//        _solution =  methodMatrix*_solution - constantMatrix;
////        std::cout << "Result: " << std::endl;
////        _solution.print();
////
////        //Print equations to file
////        for (int j = 0; j < _numberOfVariables; j++) {
////            myfile << _solution.get(0, j).toString() << '\t';
////        }
////        myfile << '\n';
//        i++;
//    } while (i < _MIN_ITERATION_NUMBER || !areSolutionsSimilar(prevSolution,  _solution, _SIMILARITY_THRESHOLD));
//    myfile.close();


    //Gauss method
    std::cout << "Creating matrix:" << std::endl;
    Matrix<ComplexFloat> equations(_numberOfVariables + 1, _numberOfVariables);
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
void MatrixSystemOfEquations::print(int y) const {
    for (int i = 0; i < _numberOfVariables; i++) {
        if (_matrix.get(i, y) != ComplexFloat(0.f,0.f)) {
            std::cout << "(" << _matrix.get(i, y).toString() << ")*x_" << i << " + ";
        }
    }
    std::cout << " = " << _values.get(0, y).toString() << std::endl;
}

//private:
bool MatrixSystemOfEquations::areSolutionsSimilar(const MapMatrix & v1, const MapMatrix & v2, float similarityThreshold) const {
    for (int i = 0; i < _numberOfVariables; i++) {
        if (std::isnan(v1.get(0, i).real) || std::isinf(v1.get(0, i).real) ||
        std::isnan(v1.get(0, i).imag) || std::isinf(v1.get(0, i).imag) ||
        std::isnan(v2.get(0, i).real) || std::isinf(v2.get(0, i).real) ||
        std::isnan(v2.get(0, i).imag) || std::isinf(v2.get(0, i).imag)) {
            std::cout << "ERROR: Unstable solution! Consider raising _NUMBER_OF_POINTS_PER_PERIOD value." << std::endl;
            return true;
        }
        ComplexFloat difference = v1.get(0, i) - v2.get(0, i);
        if (abs(difference.real) > similarityThreshold || abs(difference.imag) > similarityThreshold) {
            return false;
        }
    }
    return true;
}
bool MatrixSystemOfEquations::areNumbersSimilar(const ComplexFloat & x, const ComplexFloat & y, float similarityThreshold) const {
    ComplexFloat difference = x - y;
    return (abs(difference.real) < similarityThreshold && abs(difference.imag) < similarityThreshold);
}
