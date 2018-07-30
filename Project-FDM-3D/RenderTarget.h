#pragma once
#include "header.h"
#include "Renderable.h"
#include <glm/glm.hpp>
#include "E_TextureID.h"
#include "Tab.h"

class RenderTarget
{
	const Renderable * _renderable;
	const bool _ifAutorotated;
	const glm::vec3 _modelPosition;
	const float _yaw;
	const float _pitch;
	const glm::vec3 _axis;
	const glm::vec3 _scale;

public:
	RenderTarget(Renderable * renderable, glm::vec3 modelPosition, float yaw, float pitch, glm::vec3 normalizedPitchAxis, glm::vec3 scale);
	RenderTarget(Renderable * renderable, glm::vec3 modelPosition, float rotation, glm::vec3 rotationAxis, glm::vec3 scale);
	unsigned int getNumberOfVertices() const;
	bool getIfAutorotated() const;
	const glm::vec3 & getModelPosition() const;
	float getYaw() const;
	float getPitch() const;
	float getRotation() const;
	const glm::vec3 & getAxis() const;
	const glm::vec3 & getScale() const;
	const Tab<RenderVertex> & generateRenderVertices() const;
	const E_TextureID getTexture() const;
	~RenderTarget();
};