//
// Created by baronvladziu on 07.11.18.
//

#include "VectorSystemOfEquations.h"
#include "Matrix.h"

VectorSystemOfEquations::VectorSystemOfEquations(int numberOfVariables)
    : _numberOfVariables(numberOfVariables), _equations(_numberOfVariables),
      _values(_numberOfVariables), _solution(_numberOfVariables)
{
    for (int i = 0; i < _numberOfVariables; i++) {
        _equations[i].resetSize(_numberOfVariables);
    }
}
int VectorSystemOfEquations::getNumberOfVariables() const {
    return _numberOfVariables;
}
float VectorSystemOfEquations::get(int x, int y) const {
    return _equations[y].get(x);
}
float VectorSystemOfEquations::getConstant(int y) const {
    return _values.get(y);
}
float VectorSystemOfEquations::getSolution(int y) const {
    return _solution.get(y);
}
void VectorSystemOfEquations::set(int x, int y, float value) {
    _equations[y].set(x, value);
}
void VectorSystemOfEquations::setConstant(int y, float value) {
    _values.set(y, value);
}
void VectorSystemOfEquations::solve() {

    //--- Gauss method ---//
    std::cout << "Creating matrix:" << std::endl;
    Matrix<float> equations(_numberOfVariables + 1, _numberOfVariables);
    equations.fillWithZeros();
    for (int j = 0; j < _numberOfVariables; j++) {
        for (int i = 0; i < _numberOfVariables; i++) {
            equations.set(i, j, _equations[j].get(i));
        }
        equations.set(_numberOfVariables, j, _values.get(j));
        assert(equations.get(j, j) != 0.f);
    }
    std::cout << "Solving matrix:" << std::endl;
    equations.solve();
//    equations.print();
    std::cout << "Saving results:" << std::endl;
    for (int j = 0; j < _numberOfVariables; j++) {
        _solution.set(j, equations.get(_numberOfVariables, j));
    }
    _solution.print();


    //--- Monte Carlo method ---//
//    //Init
//    FloatVector sumNumerator(_numberOfVariables);
//    float sumDenominator = 0.f;
//    float diff = 0.f;
//    //Value range
//    float maxValue = _values.getAbsSum();
//    //Loop
//    int i = 0;
//    do {
//        //Update sum
//        FloatVector randomV(_numberOfVariables);
//        randomV.randomize(maxValue);
//        diff = calculateDiff(randomV);
//        if (diff == 0.f) {
//            _solution = randomV;
//            std::cout << "Lucky solution!" << std::endl;
//            return;
//        }
//        sumNumerator += randomV / diff;
//        sumDenominator += 1.f / diff;
//
//        //Print diff
//        diff = calculateDiff(sumNumerator/sumDenominator);
//        std::cout << "Iteration " << i << ": diff = " << diff << std::endl;
//        i++;
//    } while (diff > 1000.f);
//    _solution = sumNumerator/sumDenominator;


    //--- Better Monte Carlo method ---//
//    //Init
//    FloatVector sumNumerator(_numberOfVariables);
//    int numberOfSolutions = 100;
//    std::vector<float> diffs(numberOfSolutions);
//    //Value range
//    float maxValue = _values.getAbsSum();
//    std::vector<FloatVector> solutions(numberOfSolutions);
//    for (int s = 0; s < numberOfSolutions; s++) {
//        solutions[s].resetSize(_numberOfVariables);
//        solutions[s].randomize(maxValue);
//    }
//    //Loop
//    int iter = 0;
//    while (true) {
//        std::cout << "Iteration: " << iter << std::endl;
//        //Calculate diffs
//        for (int s = 0; s < numberOfSolutions; s++) {
//            diffs[s] = calculateDiff(solutions[s]);
//            std::cout << "Diffs[" << s << "] = " << diffs[s] << std::endl;
//            if (diffs[s] < 0.00001f) {
//                _solution = solutions[s];
//                return;
//            }
//        }
//        //Choose best solution
//        int sample = 0;
//        for (int s = 1; s < numberOfSolutions; s++) {
//            if (diffs[s] < diffs[sample]) {
//                sample = s;
//            }
//        }
//        //Randomize solutions
//        for (int s = 0; s < numberOfSolutions; s++) {
//            FloatVector noise(_numberOfVariables);
//            noise.randomize(0.001f*diffs[sample]);
//            solutions[s] = solutions[sample] + noise;
//        }
//        iter++;
//    }


    //--- Projection method ---//
//    //Normalize equations
//    for (int i = 0; i < _numberOfVariables; i++) {
//        float norm = sqrt(_equations[i]*_equations[i]);
//        _equations[i] /= norm;
//        _values.set(i, _values.get(i) / norm);
//    }
//
//    _solution.fillWithZeros();
//    float actMaxMeanVectorValue = 0.f;
//    int iterationID = 1;
//    do {
//        std::cout << "Iteration: " << iterationID << std::endl;
//
//        //Calculate mean direction vector
//        FloatVector meanDirection(_numberOfVariables);
//        meanDirection.fillWithZeros();
//        for (int i = 0; i < _numberOfVariables; i++) {
//            meanDirection -= _equations[i]*(_solution*_equations[i] + _values.get(i));
//        }
//        meanDirection /= _numberOfVariables;
//        actMaxMeanVectorValue = meanDirection.getMaxAbs();
//        std::cout << "Max mean vector value: " << actMaxMeanVectorValue << std::endl;
//
//        //Update solution
//        _solution += meanDirection;
//        _solution.print();
//
//        iterationID++;
//    } while (actMaxMeanVectorValue > 0.00001f);

    //--- Gradient descent ---//
//    //Set starting solution
//    _solution = _values;
//    //Loop
//    FloatVector diff(_numberOfVariables);
//    do {
//        //Calculate gradient
//        diff = calculateDiffVector(_solution);
//        std::cout << "Diff = " << diff.getNorm() << std::endl;
//        for (int i = 0; i < _numberOfVariables; i++) {
//            float gradient = 0.f;
//            for (int j = 0; j < _numberOfVariables; j++) {
//                gradient -= 2 * diff.get(j) * _equations[j].get(i);
//            }
//            _solution.set(i, _solution.get(i) + gradient*0.003f);
//        }
//    } while (diff.getNorm() > 1.f);
//    _solution.print();

    //--- Momentum Gradient descent ---//
//    //Calculate largest eigenvalue
//    std::cout << "\nFinding largest eigenvalue:" << std::endl;
//    FloatVector eigenvector(_numberOfVariables);
//    FloatVector temp(_numberOfVariables);
//    for (int i = 0; i < _numberOfVariables; i++) {
//        eigenvector.set(i, 1.f);
//    }
//    float prevEigenvalue;
//    float eigenvalue = eigenvector.getMax();
//    int i = 0;
//    do {
//        prevEigenvalue = eigenvalue;
//        //Transformation
//        for (int j = 0; j < _numberOfVariables; j++) {
//            temp.set(j, _equations[j]*eigenvector);
//        }
//        eigenvector = temp;
//        //Find max
//        eigenvalue = eigenvector.getMaxAbs();
//        //Normalization
//        eigenvector /= eigenvalue;
//        //Print
////        eigenvector.print();
//        std::cout << "Eigenvalue = " << eigenvalue << std::endl;
//        i++;
//    } while (i < 20 || abs(prevEigenvalue - eigenvalue) > 0.001f*i);
//    //Set gradient constants
//    float alpha = 0.001f;
//    std::cout << "alpha = " << alpha << std::endl;
//    float beta = 0.9f;
//    std::cout << "beta = " << beta << std::endl;
//    //Set starting solution
//    std::cout << "\nFinding solution:" << std::endl;
//    _solution = _values;
//    //Loop
//    FloatVector lastGradient(_numberOfVariables);
//    lastGradient.fillWithZeros();
//    FloatVector diff(_numberOfVariables);
//    float diffNorm;
//    do {
//        //Calculate gradient
//        diff = calculateDiffVector(_solution);
//        diffNorm = diff.getNorm();
//        std::cout << "Diff = " << diffNorm << std::endl;
//        for (int i = 0; i < _numberOfVariables; i++) {
//            float gradient = 0.f;
//            for (int j = 0; j < _numberOfVariables; j++) {
//                gradient -= 2 * diff.get(j) * _equations[j].get(i);
//            }
//            gradient += beta*lastGradient.get(i);
//            _solution.set(i, _solution.get(i) + gradient*alpha);
//            lastGradient.set(i, gradient);
//        }
//    } while (diffNorm > 0.01f);
//    _solution.print();


    //--- Space cut method ---//
//    //Set borders
//    float maxValue = _values.getAbsSum();
//    FloatVector lowBorders(_numberOfVariables);
//    FloatVector upBorders(_numberOfVariables);
//    for (int i = 0; i < _numberOfVariables; i++) {
//        lowBorders.set(i, -maxValue);
//        upBorders.set(i, maxValue);
//    }
//    //Loop
//    FloatVector randomPoint(_numberOfVariables);
//    FloatVector diff(_numberOfVariables);
//    do {
//        //Get random point
//        for (int i = 0; i < _numberOfVariables; i++) {
//            randomPoint.randomize(i, lowBorders.get(i), upBorders.get(i));
//        }
//        //Calculate gradient
//        diff = calculateDiffVector(randomPoint);
//        std::cout << "Diff = " << diff.getNorm() << std::endl;
//        FloatVector gradient(_numberOfVariables);
//        for (int i = 0; i < _numberOfVariables; i++) {
//            float value = 0.f;
//            for (int j = 0; j < _numberOfVariables; j++) {
//                value -= 2 * diff.get(j) * _equations[j].get(i);
//            }
//            gradient.set(i, value);
//        }
//        //Update borders
////        gradient.print();
//        for (int i = 0; i < _numberOfVariables; i++) {
//            if (gradient.get(i) > 1.f) {
//                lowBorders.set(i, randomPoint.get(i));
//            } else if (gradient.get(i) < -1.f) {
//                upBorders.set(i, randomPoint.get(i));
//            }
//        }
//
//    } while (diff.getNorm() > 0.1f);
//    _solution = randomPoint;


    //--- Variable cut method ---//
//    //Init
//    float maxValue = _values.getAbsSum();
//    _solution.randomize(maxValue);
//    for (int var = 0; var < _numberOfVariables; var++) {
//        std::cout << "--- --- Var = " << var << " of " << _numberOfVariables << " --- ---" << std::endl;
//        float minV = -maxValue;
//        float maxV = maxValue;
//        while (true) {
//            float random = minV + (((float) rand()) / (float) RAND_MAX) * (maxV - minV);
//            std::cout << "Random = " << random << std::endl;
//            if ((minV == maxV) && (minV == maxValue || minV == -maxValue)) {
//                std::cout << "Unstable variable " << var << std::endl;
//                while (true) {}
//                _solution.set(var, 0);
//                break;
//            }
//            _solution.set(var, random);
//            _solution.print();
//            float gradient = 0.f;
//            for (int j = 0; j < _numberOfVariables; j++) {
//                gradient -= 2*calculateDiffVectorValue(_solution, j)*_equations[j].get(var);
//            }
//            std::cout << "Gradient = " << gradient << std::endl;
//            if (gradient > 0.0001f) {
//                minV = random;
////                std::cout << "New minV = " << minV << std::endl;
//            } else if (gradient < -0.0001f) {
//                maxV = random;
////                std::cout << "New maxV = " << maxV << std::endl;
//            } else {
//                break;
//            }
//        }
//    }

}
void VectorSystemOfEquations::print(int y) const {
    for (int i = 0; i < _numberOfVariables; i++) {
        if (_equations[y].get(i) != 0.f) {
            std::cout << "(" << _equations[y].get(i) << ")*x_" << i << " + ";
        }
    }
    std::cout << " = " << _values.get(y) << std::endl;
}
FloatVector VectorSystemOfEquations::calculateDiffVector(const FloatVector & solution) const {
    FloatVector result(_numberOfVariables);
    for (int i = 0; i < _numberOfVariables; i++) {
        result.set(i, _equations[i]*solution - _values.get(i));
    }
    return result;
}
float VectorSystemOfEquations::calculateDiffVectorValue(const FloatVector & solution, int i) const {
    return _equations[i]*solution - _values.get(i);
}
float VectorSystemOfEquations::calculateDiff(const FloatVector & solution) const {
    FloatVector result(_numberOfVariables);
    for (int i = 0; i < _numberOfVariables; i++) {
        result.set(i, _equations[i]*solution - _values.get(i));
    }
    return result.getNorm();
}
