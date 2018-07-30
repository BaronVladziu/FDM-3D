#include "RenderRectangle.h"

RenderRectangle::RenderRectangle(ModelPoint * a, ModelPoint * b, ModelPoint * c, ModelPoint * d, E_TextureID texture)
	: _vertices(_NUMBER_OF_VERTICES), _texture(texture)
{
	_vertices[0] = a;
	_vertices[1] = b;
	_vertices[2] = c;
	_vertices[3] = d;
}
const Vector3f & RenderRectangle::getVertex(unsigned int i) const {
	return _vertices[i]->getPosition();
}
void RenderRectangle::setVertex(unsigned int i, ModelPoint * vertex) {
	_vertices[i] = vertex;
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
const Tab<ModelPoint *> & RenderRectangle::getVertices() const {
	return _vertices;
}
Vector3f RenderRectangle::getPosition() const {
	return (_vertices[0]->getPosition() + _vertices[1]->getPosition() + _vertices[2]->getPosition() + _vertices[3]->getPosition()) / 4;
}
E_TextureID RenderRectangle::getTextureID() const {
	return _texture;
}
void RenderRectangle::setTextureID(E_TextureID texID) {
	_texture = texID;
}
RenderRectangle::~RenderRectangle() {}