#pragma once
#include "header.h"
#include "ModelPoint.h"
#include "E_TextureID.h"

class Model
{
	std::list<ModelPoint *> _points;
	std::list<Renderable *> _rectangles;
	Vector3f _position;
	bool _ifAutorotated;
	float _rotation;
	Vector3f _rotationAxis;
	bool _ifAutoscaled;
	Vector3f _scale;

	void updateRotation();
	ModelPoint * findModelPoint(unsigned int id) const;

public:
	Model();
	const ModelPoint * addPoint(const Vector3f & position);
	void setPoint(ModelPoint * point, const Vector3f & position);
	const std::list<ModelPoint *> & getPoints() const;
	std::list<ModelPoint *>::iterator getPointsBegin();
	std::list<ModelPoint *>::iterator getPointsEnd();
	int getNumberOFPoints() const;
	const std::list<Renderable*> & getPlanes() const;
	std::list<Renderable *>::iterator getPlanesBegin();
	std::list<Renderable *>::iterator getPlanesEnd();
	int getNumberOFPlanes() const;
	void addTriangle(ModelPoint * a, ModelPoint * b, ModelPoint * c, E_TextureID texID);
	void addTriangle(int a, int b, int c, E_TextureID texID);
	void addRectangle(ModelPoint * a, ModelPoint * b, ModelPoint * c, ModelPoint * d, E_TextureID texID);
	void addRectangle(int a, int b, int c, int d, E_TextureID texID);
	void saveModelToFile(const std::string & fileName) const;
	void loadModelFromFile(const std::string & fileName);
	const Vector3f & getPosition() const;
	void setPosition(const Vector3f & position);
	void move(const Vector3f & position);
	bool isAutorotated() const;
	void setIfAutorotated(bool autorotate);
	const float getRotation() const;
	void setRotation(float rotation);
	void rotate(float rotation);
	const Vector3f & getRotationAxis() const;
	void setRotationAxis(const Vector3f & rotationAxis);
	bool isAutoscaled() const;
	void setIfAutoscaled(bool autoscale);
	const Vector3f & getScale() const;
	void setScale(const Vector3f & scale);
	E_TextureID getTextureID(std::list<Renderable *>::iterator plane) const;
	void setTextureID(std::list<Renderable *>::iterator plane, E_TextureID texID);
	void setTextureIDForAllPlanes(E_TextureID texID);
	~Model();
};