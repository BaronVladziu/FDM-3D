//
// Created by baronvladziu on 09.09.18.
//

#include "SolverPoint.h"


void SolverPoint::setToSource(const ComplexFloat & pressure) {
    _isSource = true;
}
void SolverPoint::setNormalVector(const glm::vec3 & vector) {
    _normalVector = vector;
}
const glm::vec3 & SolverPoint::getNormalVector() const {
    return _normalVector;
}
