#include "ModelPoint.h"

ModelPoint::ModelPoint(const Vector3f & position)
	: _position(position)
{}
void ModelPoint::addRectangle(const RenderRectangle * rect) {
	_adjacentRectangles.push_front(rect);
}
void ModelPoint::removeRectangle(const RenderRectangle * rect) {
	_adjacentRectangles.remove(rect);
}
const Vector3f & ModelPoint::getPosition() const {
	return _position;
}
void ModelPoint::setPosition(const Vector3f & position) {
	_position = position;
}
void ModelPoint::move(const Vector3f & position) {
	_position += position;
}
ModelPoint::~ModelPoint() {}