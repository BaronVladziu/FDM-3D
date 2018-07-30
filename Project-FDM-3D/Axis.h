#pragma once
#include "header.h"
#include "E_Axis.h"
#include "Vector3f.h"

class Axis
{
	E_Axis _axis;

public:
	Axis();
	Axis(E_Axis axis);
	E_Axis getAxis() const;
	char getName() const;
	Vector3f getVector() const;
	~Axis();
};