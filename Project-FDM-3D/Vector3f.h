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
	Vector3f operator-(const Vector3f & v) const;
	~Vector3f();
};