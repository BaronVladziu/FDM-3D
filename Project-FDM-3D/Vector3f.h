#pragma once
#include "header.h"

class Vector3f {
public:
	float x;
	float y;
	float z;

	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f operator+(const Vector3f & v) const;
	void operator+=(const Vector3f & v);
	Vector3f operator-(const Vector3f & v) const;
	void operator-=(const Vector3f & v);
	float distance(const Vector3f & v) const;
	void operator*=(float f);
	void operator/=(float f);
	Vector3f operator*(float f) const;
	Vector3f operator/(float f) const;
	float length() const;
	void normalize();
	~Vector3f();
};