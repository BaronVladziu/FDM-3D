#pragma once
#include "E_ActionType.h"
#include "Axis.h"
#include "E_ObjectType.h"
#include "ModelPoint.h"
#include "Renderable.h"
#include "Vector3f.h"

class Action
{
	const E_ActionType _actiontype;
	Axis _oldAxis;
	Axis _newAxis;
	E_ObjectType _oldObjectType;
	E_ObjectType _newObjectType;
	ModelPoint * _point;
	Renderable * _plane;
	std::list<bool> _objectMarks;
	Vector3f _vector;

public:
	Action(const E_ActionType actionType, Axis oldAxis, Axis newAxis);
	Action(const E_ActionType actionType, E_ObjectType oldObjectType, E_ObjectType newObjectType, std::list<bool> objectMarks);
	Action(const E_ActionType actionType);
	Action(const E_ActionType actionType, Vector3f moveVector);
	Action(const E_ActionType actionType, std::list<bool> objectMarks);
	const E_ActionType getActionType() const;
	const Axis getOldAxis() const;
	const Axis getNewAxis() const;
	const E_ObjectType getOldObjectType() const;
	const E_ObjectType getNewObjectType() const;
	const ModelPoint * getPoint() const;
	const Renderable * getPlane() const;
	const std::list<bool> & getObjectMarks() const;
	const Vector3f & getVector() const;
	~Action();
};