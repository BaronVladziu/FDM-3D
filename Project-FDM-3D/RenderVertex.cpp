#include "header.h"
#include "RenderVertex.h"
#include "Vector3f.h"

RenderVertex::RenderVertex() {}
RenderVertex::RenderVertex(float posX, float posY, float posZ, float texPosX, float texPosY)
	: _posX(posX), _posY(posY), _posZ(posZ), _texPosX(texPosX), _texPosY(texPosY)
{}
RenderVertex::RenderVertex(const Vector3f & pos, float texPosX, float texPosY)
	: _posX(pos.x), _posY(pos.y), _posZ(pos.z), _texPosX(texPosX), _texPosY(texPosY)
{}
float * RenderVertex::getData() {
	float tab[_NUMBER_OF_FLOATS] = { _posX, _posY, _posZ, _texPosX, _texPosY };
	return tab;
}
int RenderVertex::getNumberOfFloats() {
	return _NUMBER_OF_FLOATS;
}
RenderVertex::~RenderVertex() {}