#pragma once
#include "header.h"
#include "ModelPoint.h"
#include "E_TextureID.h"

class Renderable {
public:
	virtual Tab<RenderVertex> generateRenderVertices() const = 0;
	virtual unsigned int getNumberOfRenderVertices() const = 0;
	virtual const Tab<ModelPoint *> & getVertices() const = 0;
	virtual Vector3f getPosition() const = 0;
	virtual E_TextureID getTextureID() const = 0;
	virtual void setTextureID(E_TextureID texID) = 0;
};