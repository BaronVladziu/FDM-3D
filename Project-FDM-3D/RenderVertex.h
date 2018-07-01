#pragma once
#include "header.h"

class RenderVertex {

	const static int _NUMBER_OF_FLOATS = 5;

	float _posX;
	float _posY;
	float _posZ;
	float _texPosX;
	float _texPosY;

public:
	RenderVertex();
	RenderVertex(float posX, float posY, float posZ, float texPosX, float texPosY);
	RenderVertex(const Vector3f & pos, float texPosX, float texPosY);
	float * getData();
	int getNumberOfFloats();
	~RenderVertex();
};