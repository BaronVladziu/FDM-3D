#include "ActionManager.h"

void ActionManager::setActiveAxis() {
	std::cout << "Axis changed from " << _actualAction->getOldAxis().getName() << " to " << _actualAction->getNewAxis().getName() << std::endl;
	_scene.setActiveAxis(_actualAction->getNewAxis());
}
void ActionManager::reverseActiveAxis() {
	std::cout << "Axis changed from " << _actualAction->getNewAxis().getName() << " to " << _actualAction->getOldAxis().getAxis() << std::endl;
	_scene.setActiveAxis(_actualAction->getOldAxis());
}
void ActionManager::setActiveMode() {
	std::cout << "Mode changed from " << _actualAction->getOldObjectType() << " to " << _actualAction->getNewObjectType() << std::endl;
	_scene.setActiveMode(_actualAction->getNewObjectType());
}
void ActionManager::reverseActiveMode() {
	std::cout << "Mode changed from " << _actualAction->getNewObjectType() << " to " << _actualAction->getOldObjectType() << std::endl;
	_scene.setActiveMode(_actualAction->getOldObjectType());
}
void ActionManager::addPoint() {
	std::cout << "New point added." << " Position: X=" << _actualAction->getVector().x << " Position Y=" << _actualAction->getVector().y << " Position: Z=" << _actualAction->getVector().z << std::endl;
	_scene.addObject();
}
void ActionManager::deletePoint() {
	std::cout << "Point deleted." << std::endl;
	_scene.deleteObject();
}
void ActionManager::addPlane() {
	std::cout << "New plane added." << std::endl;
	_scene.addObject();
}
void ActionManager::deletePlane() {
	std::cout << "Plane deleted." << std::endl;
	_scene.deleteObject();
}
void ActionManager::addSpeaker() {
	std::cout << "New speaker added." << " Position: X=" << _actualAction->getVector().x << " Position Y=" << _actualAction->getVector().y << " Position: Z=" << _actualAction->getVector().z << std::endl;
	_scene.addObject();
}
void ActionManager::deleteSpeaker() {
	std::cout << "Speaker deleted." << std::endl;
	_scene.deleteObject();
}
void ActionManager::moveObject() {
	std::cout << "Object moved." << " Move vector: X=" << _actualAction->getVector().x << " Position Y=" << _actualAction->getVector().y << " Position: Z=" << _actualAction->getVector().z << std::endl;
	_scene.moveObject(_actualAction->getVector());
}
void ActionManager::reverseObjectMove() {
	std::cout << "Object moved." << " Move vector: X=" << -_actualAction->getVector().x << " Position Y=" << -_actualAction->getVector().y << " Position: Z=" << -_actualAction->getVector().z << std::endl;
	_scene.moveObject(_actualAction->getVector() * (-1));
}
void ActionManager::targetNext() {
	std::cout << "Next object targeted." << std::endl;
	_scene.targetNext();
}
void ActionManager::targetPrevious() {
	std::cout << "Previous object targeted." << std::endl;
	_scene.targetPrevious();
}
void ActionManager::markAll() {
	std::cout << "All objects marked." << std::endl;
	_scene.markUnmarkAll();
}
void ActionManager::reverseMarkAll() {
	std::cout << "Objects marked." << std::endl;
	_scene.markObjects(_actualAction->getObjectMarks());
}
void ActionManager::mark() {
	std::cout << "Object marked." << std::endl;
	_scene.markUnmarkTarget();
}
void ActionManager::unmark() {
	std::cout << "Object unmarked." << std::endl;
	_scene.markUnmarkTarget();
}
void ActionManager::executeActualAction() {
	switch (_actualAction->getActionType()) {
	case E_ActionType::SetActiveAxis:
		setActiveAxis();
		break;
	case E_ActionType::SetActiveMode:
		setActiveMode();
		break;
	case E_ActionType::AddPoint:
		addPoint();
		break;
	case E_ActionType::AddPlane:
		addPlane();
		break;
	case E_ActionType::AddSpeaker:
		addSpeaker();
		break;
	case E_ActionType::DeletePoint:
		deletePoint();
		break;
	case E_ActionType::DeletePlane:
		deletePlane();
		break;
	case E_ActionType::DeleteSpeaker:
		deleteSpeaker();
		break;
	case E_ActionType::MoveObject:
		moveObject();
		break;
	case E_ActionType::TargetNext:
		targetNext();
		break;
	case E_ActionType::TargetPrevious:
		targetPrevious();
		break;
	case E_ActionType::MarkAll:
		markAll();
		break;
	case E_ActionType::Mark:
		mark();
		break;
	case E_ActionType::Unmark:
		unmark();
		break;
	default:
		std::cout << "Error: Unsupported action type!" << std::endl;
		break;
	}
}
void ActionManager::reverseActualAction() {
	switch (_actualAction->getActionType()) {
	case E_ActionType::SetActiveAxis: //2*enum
		reverseActiveAxis();
		break;
	case E_ActionType::SetActiveMode: //2*enum + IDs
		reverseActiveMode();
		break;
	case E_ActionType::AddPoint: //ID + position
		deletePoint();
		break;
	case E_ActionType::AddPlane: //(x+1)*ID
		deletePlane();
		break;
	case E_ActionType::AddSpeaker: //ID + position
		deleteSpeaker();
		break;
	case E_ActionType::DeletePoint: //ID + position
		addPoint();
		break;
	case E_ActionType::DeletePlane: //(x+1)*ID
		addPlane();
		break;
	case E_ActionType::DeleteSpeaker: //ID + position
		addSpeaker();
		break;
	case E_ActionType::MoveObject: //ID + vector
		reverseObjectMove();
		break;
	case E_ActionType::TargetNext: //enum + ID
		targetPrevious(); //TODO
		break;
	case E_ActionType::TargetPrevious: //enum + ID
		targetNext(); //TODO
		break;
	case E_ActionType::MarkAll: //IDs
		reverseMarkAll();
		break;
	case E_ActionType::Mark: //enum + ID
		unmark();
		break;
	case E_ActionType::Unmark: //enum + ID
		mark();
		break;
	default:
		std::cout << "Error: Unsupported action type!" << std::endl;
		break;
	}
}

ActionManager::ActionManager(Scene & scene)
	: _scene(scene), _actualAction(_actions.begin())
{}
void ActionManager::undo() {
	if (_actualAction != _actions.begin()) {
		reverseActualAction();
		_actualAction--;
	}
}
void ActionManager::redo() {
	if (_actions.size() > 1) {
		std::list<Action>::iterator it = _actualAction;
		if (++it != _actions.end()) {
			_actualAction++;
			executeActualAction();
		}
	}
}
void ActionManager::executeAction(const Action & action) {
	if (_actualAction != _actions.end()) {
		std::list<Action>::iterator it = _actualAction;
		_actions.erase(++it, _actions.end());
	}
	_actions.push_back(action);
	if (_actions.size() == 1) {
		_actualAction = _actions.begin();
	}
	else {
		_actualAction++;
	}
	executeActualAction();
}
ActionManager::~ActionManager()
{}