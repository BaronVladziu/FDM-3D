//
// Created by baronvladziu on 09.09.18.
//

#ifndef VULKAN_FDM_COMPLEXFLOAT_H
#define VULKAN_FDM_COMPLEXFLOAT_H

#include "header.h"


class ComplexFloat {

public:
    float real;
    float imag;

    ComplexFloat() = default;
    ComplexFloat(float realPart, float imaginaryPart);
    ComplexFloat operator+(const ComplexFloat & x) const;
    void operator+=(const ComplexFloat & x);
    ComplexFloat operator-(const ComplexFloat & x) const;
    void operator-=(const ComplexFloat & x);
    ComplexFloat operator*(const ComplexFloat & x) const;
    ComplexFloat operator*(const float & k) const;
    ComplexFloat operator/(const ComplexFloat & x) const;
    void operator/=(const ComplexFloat & x);
    ComplexFloat operator/(const float & k) const;
    bool operator==(const ComplexFloat & x) const;
    bool operator!=(const ComplexFloat & x) const;
    std::string toString() const;

};


#endif //VULKAN_FDM_COMPLEXFLOAT_H
