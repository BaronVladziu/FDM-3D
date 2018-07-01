#pragma once
#include "header.h"

class Renderable {
public:
	virtual Tab<RenderVertex> generateRenderVertices() const = 0;
	virtual unsigned int getNumberOfRenderVertices() const = 0;
};