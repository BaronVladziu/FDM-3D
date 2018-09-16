//
// Created by baronvladziu on 09.09.18.
//

#ifndef VULKAN_FDM_COMPLEXFLOAT_H
#define VULKAN_FDM_COMPLEXFLOAT_H


class ComplexFloat {

public:
    float real;
    float imag;

    ComplexFloat() = default;
    ComplexFloat(float realPart, float imaginaryPart);
    ComplexFloat operator+(const ComplexFloat & x) const;
    ComplexFloat operator-(const ComplexFloat & x) const;
    ComplexFloat operator*(const float & k) const;
    ComplexFloat operator/(const float & k) const;

};


#endif //VULKAN_FDM_COMPLEXFLOAT_H
