#pragma once
#include "header.h"
#include <glad/glad.h>
#include "Tab.h"
#include "Model.h"
#include "Action.h"
#include "E_InputAction.h"
#include "ActionManager.h"
#include "Renderable.h"

class Scene
{
	const float _OBJECT_MOVE_SPEED;

	friend class ActionManager;
	ActionManager * _actionManager;
	

	Model _map;
	Model _speakerMap;

	std::list<Model *> _pointModels;
	std::list<bool> _pointMarks;
	int _numberOfPointMarks;
	std::list<ModelPoint *>::iterator _targetPoint;
	std::list<Model *>::iterator _targetPointModel;
	std::list<bool>::iterator _targetPointMark;

	std::list<bool> _planeMarks;
	int _numberOfPlaneMarks;
	std::list<Renderable *>::iterator _targetPlane;
	std::list<bool>::iterator _targetPlaneMark;

	std::list<Model *> _speakerModels;
	std::list<bool> _speakerMarks;
	int _numberOfSpeakerMarks;
	std::list<ModelPoint *>::iterator _targetSpeaker;
	std::list<Model *>::iterator _targetSpeakerModel;
	std::list<bool>::iterator _targetSpeakerMark;

	Model _arrow;
	Model _target;
	E_ObjectType _actualMode;
	Axis _actualActiveAxis;

	std::list<const Model *> _models;


	void setActiveAxis(const Axis & newAxis);
	void setActiveMode(E_ObjectType newMode);
	void addObject();
	void deleteObject();
	void moveObject(const Vector3f & vector);
	void targetNext();
	void targetPrevious();
	void markUnmarkAll();
	void markUnmarkTarget();
	void markObjects(const std::list<bool> & marks);

	bool isObjectAlive();
	bool isPointOrSpeakerAlive();
	bool isAtLeastOneObject();
	bool isActionAvaliable(const E_InputAction inputAction);
	void sendAction(const E_InputAction inputAction);

public:
	Scene();
	const std::list<const Model *> & getModels();
	void update(float deltaTime);
	void orderAction(const E_InputAction inputAction);
	~Scene();
};