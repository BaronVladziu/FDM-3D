//
// Created by baronvladziu on 09.09.18.
//

#ifndef VULKAN_FDM_SOLVERPOINT_H
#define VULKAN_FDM_SOLVERPOINT_H

#include <glm/vec3.hpp>
#include "ComplexFloat.h"


class SolverPoint {

    glm::vec3 _normalVector = glm::vec3(0,0,0);
    bool _isSource = false;
    ComplexFloat _sourcePressure;

public:
    void setToSource(const ComplexFloat & pressure);
    void setNormalVector(const glm::vec3 & vector);
    const glm::vec3 & getNormalVector() const;

};


#endif //VULKAN_FDM_SOLVERPOINT_H
