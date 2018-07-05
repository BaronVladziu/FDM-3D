#pragma once
#include "header.h"
#include "Renderable.h"
#include "Vector3f.h"
#include "Tab.h"
#include "ModelPoint.h"

class RenderRectangle
	: public Renderable
{
	const static int _NUMBER_OF_VERTICES = 4;
	const static int _NUMBER_OF_RENDER_VERTICES = 6;

	const std::vector<ModelPoint*> & _modelPoints;
	Tab<int> _vertices;

public:
	RenderRectangle(const std::vector<ModelPoint*> & modelPoints);
	RenderRectangle(const std::vector<ModelPoint*> & modelPoints, int a, int b, int c, int d);
	const Vector3f & getVertex(unsigned int i) const;
	void setVertex(unsigned int i, int vertexID);
	Tab<RenderVertex> generateRenderVertices() const;
	unsigned int getNumberOfVertices() const;
	unsigned int getNumberOfRenderVertices() const;
	const Tab<int> & getVerticeIDs() const;
	~RenderRectangle();
};