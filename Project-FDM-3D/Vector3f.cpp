#include "Vector3f.h"

Vector3f::Vector3f()
	: x(0.f), y(0.f), z(0.f)
{}
Vector3f::Vector3f(float x, float y, float z)
	: x(x), y(y), z(z)
{}
Vector3f Vector3f::operator+(const Vector3f & v) const {
	return Vector3f(x + v.x, y + v.y, z + v.z);
}
void Vector3f::operator+=(const Vector3f & v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
Vector3f Vector3f::operator-(const Vector3f & v) const {
	return Vector3f(x - v.x, y - v.y, z - v.z);
}
void Vector3f::operator-=(const Vector3f & v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
float Vector3f::distance(const Vector3f & v) const {
	return operator-(v).length();
}
void Vector3f::operator*=(float f) {
	x *= f;
	y *= f;
	z *= f;
}
void Vector3f::operator/=(float f) {
	x /= f;
	y /= f;
	z /= f;
}
Vector3f Vector3f::operator*(float f) const {
	return Vector3f(x*f, y*f, z*f);
}
Vector3f Vector3f::operator/(float f) const {
	return Vector3f(x/f, y/f, z/f);
}
float Vector3f::length() const {
	return sqrt(x*x + y*y + z*z);
}
void Vector3f::normalize() {
	operator/=(length());
}
Vector3f::~Vector3f() {}