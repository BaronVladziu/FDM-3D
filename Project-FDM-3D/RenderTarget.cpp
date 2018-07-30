#include "RenderTarget.h"

RenderTarget::RenderTarget(Renderable * renderable, glm::vec3 modelPosition, float yaw, float pitch, glm::vec3 normalizedPitchAxis, glm::vec3 scale)
	: _renderable(renderable), _ifAutorotated(true), _modelPosition(modelPosition), _yaw(yaw), _pitch(pitch), _axis(normalizedPitchAxis), _scale(scale)
{}
RenderTarget::RenderTarget(Renderable * renderable, glm::vec3 modelPosition, float rotation, glm::vec3 rotationAxis, glm::vec3 scale)
	: _renderable(renderable), _ifAutorotated(false), _modelPosition(modelPosition), _yaw(rotation), _pitch(0.f), _axis(rotationAxis), _scale(scale)
{}
unsigned int RenderTarget::getNumberOfVertices() const {
	return _renderable->getNumberOfRenderVertices();
}
bool RenderTarget::getIfAutorotated() const {
	return _ifAutorotated;
}
const glm::vec3 & RenderTarget::getModelPosition() const {
	return _modelPosition;
}
float RenderTarget::getYaw() const {
	return _yaw;
}
float RenderTarget::getPitch() const {
	return _pitch;
}
float RenderTarget::getRotation() const {
	return _yaw;
}
const glm::vec3 & RenderTarget::getAxis() const {
	return _axis;
}
const glm::vec3 & RenderTarget::getScale() const {
	return _scale;
}
const Tab<RenderVertex> & RenderTarget::generateRenderVertices() const {
	return _renderable->generateRenderVertices();
}
const E_TextureID RenderTarget::getTexture() const {
	return _renderable->getTextureID();
}
RenderTarget::~RenderTarget()
{}