#pragma once
#include "header.h"
#include "Renderable.h"
#include "Vector3f.h"
#include "Tab.h"

class RenderRectangle
	: public Renderable
{
	const static int _NUMBER_OF_VERTICES = 4;
	const static int _NUMBER_OF_FLOATS = 4;

	Vector3f _vertices[_NUMBER_OF_VERTICES];
	Tab<RenderVertex> _renderVertices;

public:
	RenderRectangle();
	RenderRectangle(const Vector3f & a, const Vector3f & b, const Vector3f & c, const Vector3f & d);
	const Vector3f & getVertex(unsigned int i) const;
	void setVertex(unsigned int i, const Vector3f & v);
	Tab<RenderVertex> & getVertices();
	~RenderRectangle();
};