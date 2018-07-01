#pragma once
#include "header.h"

class Renderable {
public:
	virtual Tab<RenderVertex> & getVertices() = 0;
};