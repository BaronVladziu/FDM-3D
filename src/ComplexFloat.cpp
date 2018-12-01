//
// Created by baronvladziu on 09.09.18.
//

#include "ComplexFloat.h"


ComplexFloat::ComplexFloat()
    : real(0.f), imag(0.f)
{}
ComplexFloat::ComplexFloat(float realPart)
    : real(realPart), imag(0.f)
{}
ComplexFloat::ComplexFloat(float realPart, float imaginaryPart)
    : real(realPart), imag(imaginaryPart)
{}
ComplexFloat ComplexFloat::getRoot(int p) const {
    float resultAbs = float(std::pow(abs(), 1/p));
    float resultPhase = phase() / p;
    return ComplexFloat(resultAbs*std::cos(resultPhase), resultAbs*std::sin(resultPhase));
}
ComplexFloat ComplexFloat::getConjugate() const {
    return ComplexFloat(real, -imag);
}
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
void ComplexFloat::operator/=(float k) {
    real /= k;
    imag /= k;
}
ComplexFloat ComplexFloat::operator/(const float & k) const {
    return ComplexFloat(real / k, imag / k);
}
bool ComplexFloat::operator==(const ComplexFloat & x) const {
    return (real == x.real && imag == x.imag);
}
bool ComplexFloat::operator==(float x) const {
    return (real == x && imag == 0.f);
}
bool ComplexFloat::operator!=(const ComplexFloat & x) const {
    return (real != x.real || imag != x.imag);
}
bool ComplexFloat::operator!=(float x) const {
    return (real != x || imag != 0.f);
}
float ComplexFloat::abs() const {
    return std::sqrt(real*real + imag*imag);
}
float ComplexFloat::phase() const {
    if (real == 0) {
        if (imag == 0) {
            return 0;
        } else if (imag > 0) {
            return M_PI/2;
        } else {
            return M_PI*3/2;
        }
    } else if (real > 0) {
        return std::atan(imag/real);
    } else {
        return M_PI - std::atan(imag/real);
    }
}
std::string ComplexFloat::toString() const {
    if (imag >= 0) {
        return std::to_string(real) + "+" + std::to_string(imag) + "i";
    } else {
        return std::to_string(real) + std::to_string(imag) + "i";
    }
}
