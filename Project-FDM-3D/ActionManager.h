#pragma once
#include "header.h"
#include "Action.h"
#include "Scene.h"

class ActionManager
{
	Scene & _scene;

	std::list<Action> _actions;
	std::list<Action>::iterator _actualAction;

	void setActiveAxis();
	void reverseActiveAxis();
	void setActiveMode();
	void reverseActiveMode();
	void addPoint();
	void deletePoint();
	void addPlane();
	void deletePlane();
	void addSpeaker();
	void deleteSpeaker();
	void moveObject();
	void reverseObjectMove();
	void targetNext();
	void targetPrevious();
	void markAll();
	void reverseMarkAll();
	void mark();
	void unmark();
	void executeActualAction();
	void reverseActualAction();

public:
	ActionManager(Scene & scene);
	void undo();
	void redo();
	void executeAction(const Action & action);
	~ActionManager();
};
