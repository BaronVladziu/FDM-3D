#pragma once
#include "header.h"
#include "ModelPoint.h"

class Model
{
	std::vector<ModelPoint*> _points;
	std::list<int> _emptyPoints;
	std::list<Renderable*> _rectangles;

public:
	Model();
	const std::list<Renderable*> & getRenderables();
	//TODO: const ModelPoint * getPoint(coœtam) const;
	//TODO: load from file
	const ModelPoint * addPoint(const Vector3f & position);
	void setPoint(ModelPoint * point, const Vector3f & position);
	void setRectangle(int a, int b, int c, int d);
	void saveModelToFile(const std::string & fileName) const;
	void loadModelFromFile(const std::string & fileName);
	~Model();
};