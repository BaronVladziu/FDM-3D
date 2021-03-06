//
// Created by baronvladziu on 09.09.18.
//

#include "SolverPoint.h"


void SolverPoint::setToSource(const ComplexFloat & pressure) {
    _isSource = true;
    _sourcePressure = pressure;
}
void SolverPoint::setNormalVector(const glm::vec3 & vector) {
    _normalVector = vector;
}
const glm::vec3 & SolverPoint::getNormalVector() const {
    return _normalVector;
}
bool SolverPoint::isSource() const {
    return _isSource;
}
const ComplexFloat & SolverPoint::getPressure() const {
    return _sourcePressure;
}
