#include "header.h"
#include "RenderRectangle.h"
#include "Tab.h"
#include "RenderVertex.h"

RenderRectangle::RenderRectangle(const std::vector<ModelPoint*> & modelPoints)
	: _modelPoints(modelPoints), _vertices(_NUMBER_OF_VERTICES)
{
	for (int i = 0; i < _NUMBER_OF_VERTICES; i++) {
		_vertices[i] = -1;
	}
}
RenderRectangle::RenderRectangle(const std::vector<ModelPoint*> & modelPoints, int a, int b, int c, int d)
	: _modelPoints(modelPoints), _vertices(_NUMBER_OF_VERTICES)
{
	_vertices[0] = a;
	_vertices[1] = b;
	_vertices[2] = c;
	_vertices[3] = d;
}
const Vector3f & RenderRectangle::getVertex(unsigned int i) const {
	return _modelPoints[_vertices[i]]->getPosition();
}
void RenderRectangle::setVertex(unsigned int i, int vertexID) {
	_vertices[i] = vertexID;
}
Tab<RenderVertex> RenderRectangle::generateRenderVertices() const {
	Tab<RenderVertex> _renderVertices(_NUMBER_OF_RENDER_VERTICES);
	_renderVertices[0] = RenderVertex(getVertex(0), 0.f, 0.f);
	_renderVertices[1] = RenderVertex(getVertex(1), 1.f, 0.f);
	_renderVertices[2] = RenderVertex(getVertex(2), 1.f, 1.f);
	_renderVertices[3] = RenderVertex(getVertex(2), 1.f, 1.f);
	_renderVertices[4] = RenderVertex(getVertex(3), 0.f, 1.f);
	_renderVertices[5] = RenderVertex(getVertex(0), 0.f, 0.f);
	return _renderVertices;
}
unsigned int RenderRectangle::getNumberOfVertices() const {
	return _NUMBER_OF_VERTICES;
}
unsigned int RenderRectangle::getNumberOfRenderVertices() const {
	return _NUMBER_OF_RENDER_VERTICES;
}
const Tab<int> & RenderRectangle::getVerticeIDs() const {
	return _vertices;
}
RenderRectangle::~RenderRectangle() {}