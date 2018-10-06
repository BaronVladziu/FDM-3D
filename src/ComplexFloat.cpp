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
void ComplexFloat::operator+=(const ComplexFloat & x) {
    real += x.real;
    imag += x.imag;
}
ComplexFloat ComplexFloat::operator-(const ComplexFloat & x) const {
    return ComplexFloat(real - x.real, imag - x.imag);
}
void ComplexFloat::operator-=(const ComplexFloat & x) {
    real -= x.real;
    imag -= x.imag;
}
ComplexFloat ComplexFloat::operator*(const ComplexFloat & x) const {
    return ComplexFloat((real * x.real) - (imag * x.imag), (imag * x.real) + (real * x.imag));
}
ComplexFloat ComplexFloat::operator*(const float & k) const {
    return ComplexFloat(real * k, imag * k);
}
ComplexFloat ComplexFloat::operator/(const ComplexFloat & x) const {
    float m = (x.real * x.real) + (x.imag * x.imag);
    return ComplexFloat(((real * x.real) + (imag * x.imag))/m,
            ((imag * x.real) + (real * x.imag))/m);
}
void ComplexFloat::operator/=(const ComplexFloat & x) {
    float m = (x.real * x.real) + (x.imag * x.imag);
    real = ((real * x.real) + (imag * x.imag))/m;
    imag = ((imag * x.real) + (real * x.imag))/m;
}
ComplexFloat ComplexFloat::operator/(const float & k) const {
    return ComplexFloat(real / k, imag / k);
}
bool ComplexFloat::operator==(const ComplexFloat & x) const {
    return (real == x.real && imag == x.imag);
}
bool ComplexFloat::operator!=(const ComplexFloat & x) const {
    return (real != x.real || imag != x.imag);
}
std::string ComplexFloat::toString() const {
    if (imag >= 0) {
        return std::to_string(real) + "+" + std::to_string(imag) + "i";
    } else {
        return std::to_string(real) + std::to_string(imag) + "i";
    }
}
