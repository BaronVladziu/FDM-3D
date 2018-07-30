#pragma once
#include "header.h"
#include "Vector3f.h"

class ModelPoint
{
	Vector3f _position;
	std::list<const RenderRectangle *> _adjacentRectangles;

public:
	ModelPoint(const Vector3f & position);
	void addRectangle(const RenderRectangle * rect);
	void removeRectangle(const RenderRectangle * rect);
	const Vector3f & getPosition() const;
	void setPosition(const Vector3f & position);
	void move(const Vector3f & position);
	~ModelPoint();
};