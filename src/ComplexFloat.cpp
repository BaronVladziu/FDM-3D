//
// Created by baronvladziu on 09.09.18.
//

#include "ComplexFloat.h"


ComplexFloat::ComplexFloat(float realPart, float imaginaryPart)
    : real(realPart), imag(imaginaryPart)
{}
ComplexFloat ComplexFloat::operator+(const ComplexFloat & x) const {
    return ComplexFloat(real + x.real, imag + x.imag);
}
ComplexFloat ComplexFloat::operator-(const ComplexFloat & x) const {
    return ComplexFloat(real - x.real, imag - x.imag);
}
ComplexFloat ComplexFloat::operator*(const float & k) const {
    return ComplexFloat(real * k, imag * k);
}
ComplexFloat ComplexFloat::operator/(const float & k) const {
    return ComplexFloat(real / k, imag / k);
}