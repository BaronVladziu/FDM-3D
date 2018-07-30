#pragma once
#include "header.h"
#include "Renderable.h"
#include "Vector3f.h"
#include "Tab.h"
#include "ModelPoint.h"
#include "E_TextureID.h"
#include "RenderVertex.h"

class RenderRectangle
	: public Renderable
{
	const static int _NUMBER_OF_VERTICES = 4;
	const static int _NUMBER_OF_RENDER_VERTICES = 6;

	Tab<ModelPoint *> _vertices;
	E_TextureID _texture;

public:
	RenderRectangle(ModelPoint * a, ModelPoint * b, ModelPoint * c, ModelPoint * d, E_TextureID texture);
	const Vector3f & getVertex(unsigned int i) const;
	void setVertex(unsigned int i, ModelPoint * vertex);
	Tab<RenderVertex> generateRenderVertices() const;
	unsigned int getNumberOfVertices() const;
	unsigned int getNumberOfRenderVertices() const;
	const Tab<ModelPoint *> & getVertices() const;
	Vector3f getPosition() const;
	E_TextureID getTextureID() const;
	void setTextureID(E_TextureID texID);
	~RenderRectangle();
};