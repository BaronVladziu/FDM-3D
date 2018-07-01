#include "header.h"
#include "RenderRectangle.h"
#include "Tab.h"
#include "RenderVertex.h"

RenderRectangle::RenderRectangle()
	: _renderVertices(_NUMBER_OF_VERTICES)
{}
RenderRectangle::RenderRectangle(const Vector3f & a, const Vector3f & b, const Vector3f & c, const Vector3f & d)
	: _vertices{ a, b, c, d }, _renderVertices(_NUMBER_OF_VERTICES)
{}
const Vector3f & RenderRectangle::getVertex(unsigned int i) const {
	return _vertices[i];
}
void RenderRectangle::setVertex(unsigned int i, const Vector3f & v) {
	_vertices[i] = v;
}
Tab<RenderVertex> & RenderRectangle::getVertices() {
	_renderVertices[0] = RenderVertex(_vertices[0], 0.f, 0.f);
	_renderVertices[1] = RenderVertex(_vertices[1], 1.f, 0.f);
	_renderVertices[2] = RenderVertex(_vertices[2], 1.f, 1.f);
	_renderVertices[3] = RenderVertex(_vertices[3], 0.f, 1.f);
	return _renderVertices;
}
RenderRectangle::~RenderRectangle() {}