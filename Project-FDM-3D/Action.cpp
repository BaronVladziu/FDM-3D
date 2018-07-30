#include "Action.h"

Action::Action(const E_ActionType actionType, Axis oldAxis, Axis newAxis)
	: _actiontype(actionType), _oldAxis(oldAxis), _newAxis(newAxis)
{}
Action::Action(const E_ActionType actionType, E_ObjectType oldObjectType, E_ObjectType newObjectType, std::list<bool> objectMarks)
	: _actiontype(actionType), _oldObjectType(oldObjectType), _newObjectType(newObjectType), _objectMarks(objectMarks)
{}
Action::Action(const E_ActionType actionType)
	: _actiontype(actionType)
{}
Action::Action(const E_ActionType actionType, Vector3f moveVector)
	: _actiontype(actionType), _vector(moveVector)
{}
Action::Action(const E_ActionType actionType, std::list<bool> objectMarks)
	: _actiontype(actionType), _objectMarks(objectMarks)
{}
const E_ActionType Action::getActionType() const {
	return _actiontype;
}
const Axis Action::getOldAxis() const {
	std::cout << "Error: Accessed action parameter might be unused (TODO)!" << std::endl; //TODO
	return _oldAxis;
}
const Axis Action::getNewAxis() const {
	std::cout << "Error: Accessed action parameter might be unused (TODO)!" << std::endl; //TODO
	return _newAxis;
}
const E_ObjectType Action::getOldObjectType() const {
	std::cout << "Error: Accessed action parameter might be unused (TODO)!" << std::endl; //TODO
	return _oldObjectType;
}
const E_ObjectType Action::getNewObjectType() const {
	std::cout << "Error: Accessed action parameter might be unused (TODO)!" << std::endl; //TODO
	return _newObjectType;
}
const ModelPoint * Action::getPoint() const {
	std::cout << "Error: Accessed action parameter might be unused (TODO)!" << std::endl; //TODO
	return _point;
}
const Renderable * Action::getPlane() const {
	std::cout << "Error: Accessed action parameter might be unused (TODO)!" << std::endl; //TODO
	return _plane;
}
const std::list<bool> & Action::getObjectMarks() const {
	std::cout << "Error: Accessed action parameter might be unused (TODO)!" << std::endl; //TODO
	return _objectMarks;
}
const Vector3f & Action::getVector() const {
	std::cout << "Error: Accessed action parameter might be unused (TODO)!" << std::endl; //TODO
	return _vector;
}
Action::~Action()
{}