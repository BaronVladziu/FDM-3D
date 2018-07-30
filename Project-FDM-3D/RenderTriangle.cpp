#include "RenderTriangle.h"

RenderTriangle::RenderTriangle(ModelPoint * a, ModelPoint * b, ModelPoint * c, E_TextureID texture)
	: _vertices(_NUMBER_OF_VERTICES), _texture(texture)
{
	_vertices[0] = a;
	_vertices[1] = b;
	_vertices[2] = c;
}
const Vector3f & RenderTriangle::getVertex(unsigned int i) const {
	return _vertices[i]->getPosition();
}
void RenderTriangle::setVertex(unsigned int i, ModelPoint * vertex) {
	_vertices[i] = vertex;
}
Tab<RenderVertex> RenderTriangle::generateRenderVertices() const {
	Tab<RenderVertex> _renderVertices(_NUMBER_OF_RENDER_VERTICES);
	_renderVertices[0] = RenderVertex(getVertex(0), 0.f, 0.f);
	_renderVertices[1] = RenderVertex(getVertex(1), 1.f, 0.f);
	_renderVertices[2] = RenderVertex(getVertex(2), 1.f, 1.f);
	return _renderVertices;
}
unsigned int RenderTriangle::getNumberOfVertices() const {
	return _NUMBER_OF_VERTICES;
}
unsigned int RenderTriangle::getNumberOfRenderVertices() const {
	return _NUMBER_OF_RENDER_VERTICES;
}
const Tab<ModelPoint *> & RenderTriangle::getVertices() const {
	return _vertices;
}
Vector3f RenderTriangle::getPosition() const {
	return (_vertices[0]->getPosition() + _vertices[1]->getPosition() + _vertices[2]->getPosition()) / 3;
}
E_TextureID RenderTriangle::getTextureID() const {
	return _texture;
}
void RenderTriangle::setTextureID(E_TextureID texID) {
	_texture = texID;
}
RenderTriangle::~RenderTriangle() {}