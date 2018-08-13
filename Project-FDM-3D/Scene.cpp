#include "Scene.h"

void Scene::setActiveAxis(const Axis & newAxis) {
	_actualActiveAxis = newAxis;
	switch (newAxis.getAxis()) {
	case E_Axis::X:
		_arrow.setRotationAxis(Vector3f(1.f, 0.f, 0.f));
		_arrow.setRotation(0.f);
		break;
	case E_Axis::Y:
		_arrow.setRotationAxis(Vector3f(0.f, 0.f, 1.f));
		_arrow.setRotation(90.f);
		break;
	case E_Axis::Z:
		_arrow.setRotationAxis(Vector3f(0.f, 1.f, 0.f));
		_arrow.setRotation(-90.f);
		break;
	default:
		std::cout << "Error: Unsupported axis!" << std::endl;
		break;
	}
}
void Scene::setActiveMode(E_ObjectType newMode) {
	_actualMode = newMode;
	switch (_actualMode) {
	case E_ObjectType::Point:
		if (_targetPoint != _map.getPointsEnd()) {
			_arrow.setPosition((*_targetPoint)->getPosition());
			_target.setPosition((*_targetPoint)->getPosition());
		}
		break;
	case E_ObjectType::Plane:
		if (_targetPlane != _map.getPlanesEnd()) {
			_arrow.setPosition((*_targetPlane)->getPosition());
			_target.setPosition((*_targetPlane)->getPosition());
		}
		break;
	case E_ObjectType::Speaker:
		if (_targetSpeaker != _speakerMap.getPointsEnd()) {
			_arrow.setPosition((*_targetSpeaker)->getPosition());
			_target.setPosition((*_targetSpeaker)->getPosition());
		}
		break;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
}
void Scene::addPoint(const Vector3f & position) {
	Model * point = new Model();
	point->loadModelFromFile("Models/point");
	point->setPosition(position);
	point->setScale(Vector3f(0.02f, 0.02f, 0.02f));
	point->setIfAutoscaled(true);
	_map.addPoint(position);
	_pointModels.push_back(point);
	_pointMarks.push_back(false);
}
void Scene::addPlane(const std::list<bool> & marks) {
	int counter = 0;
	std::list<ModelPoint *>::iterator it = _map.getPointsBegin();
	for (bool mark : marks) {
		if (mark == true) {
			counter++;
		}
	}
	Tab<ModelPoint *> tab(counter);
	counter = 0;
	it = _map.getPointsBegin();
	for (bool mark : marks) {
		if (mark == true) {
			tab[counter] = *it;
			counter++;
		}
		it++;
	}
	addPlane(tab);
}
void Scene::addPlane(const Tab<ModelPoint *> & points) {
	switch (points.getSize()) {
	case 3:
		_map.addTriangle(points[0], points[1], points[2], E_TextureID::Plane);
		break;
	case 4:
		_map.addRectangle(points[0], points[1], points[2], points[3], E_TextureID::Plane);
		break;
	default:
		std::cout << "Error: Unsupported plane type!" << std::endl;
		return;
	}
	_planeMarks.push_back(false);
}
void Scene::addSpeaker(const Vector3f & position) {
	Model * speaker = new Model();
	speaker->loadModelFromFile("Models/speaker");
	speaker->setPosition(position);
	speaker->setScale(Vector3f(0.02f, 0.02f, 0.02f));
	speaker->setIfAutoscaled(true);
	_speakerMap.addPoint(position);
	_speakerModels.push_back(speaker);
	_speakerMarks.push_back(false);
}
void Scene::deleteObject(const std::list<bool> & marks) {
	switch (_actualMode) {
	case E_ObjectType::Point:
		std::list<ModelPoint *>::iterator pointIt = _map.getPointsBegin();
		std::list<Model *>::iterator modelIt = _pointModels.begin();
		std::list<bool>::iterator markIt = _pointMarks.begin();
		while (markIt != _pointMarks.end()) {
			if (*markIt == true) {
				_map.deletePoint();

				Model * point = new Model();
				point->loadModelFromFile("Models/point");
				point->setPosition(position);
				point->setScale(Vector3f(0.02f, 0.02f, 0.02f));
				point->setIfAutoscaled(true);
				_map.addPoint(position);
				_pointModels.push_back(point);
				_pointMarks.push_back(false);
			}
		}
		break;
	case E_ObjectType::Plane:
		
		break;
	case E_ObjectType::Speaker:

		break;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
}
void Scene::moveObject(const Vector3f & vector) {
	switch (_actualMode) {
	case E_ObjectType::Point:
		if (*_targetPointMark == false) {
			(*_targetPoint)->move(vector);
			(*_targetPointModel)->move(vector);
		}
		else {
			std::list<ModelPoint *>::iterator pointIt = _map.getPointsBegin();
			std::list<Model *>::iterator pointModelIt = _pointModels.begin();
			std::list<bool>::iterator markIt = _pointMarks.begin();
			while (pointIt != _map.getPointsEnd()) {
				if (*markIt == true) {
					(*pointIt)->move(vector);
					(*pointModelIt)->move(vector);
				}
				pointIt++;
				pointModelIt++;
				markIt++;
			}
		}
		break;
	case E_ObjectType::Plane:
		std::cout << "Error: Attempted to move plane!" << std::endl;
		break;
	case E_ObjectType::Speaker:
		if (*_targetSpeakerMark == false) {
			(*_targetSpeaker)->move(vector);
			(*_targetSpeakerModel)->move(vector);
		}
		else {
			std::list<ModelPoint *>::iterator speakerIt = _speakerMap.getPointsBegin();
			std::list<Model *>::iterator speakerModelIt = _speakerModels.begin();
			std::list<bool>::iterator markIt = _speakerMarks.begin();
			while (speakerIt != _speakerMap.getPointsEnd()) {
				if (*markIt == true) {
					(*speakerIt)->move(vector);
					(*speakerModelIt)->move(vector);
				}
				speakerIt++;
				speakerModelIt++;
				markIt++;
			}
		}
		break;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
	_target.move(vector);
	_arrow.move(vector);
}
void Scene::targetNext() {
	switch (_actualMode) {
	case E_ObjectType::Point:
		if (_targetPoint == _map.getPointsEnd() || _targetPoint == --_map.getPointsEnd()) {
			_targetPoint = _map.getPointsBegin();
			_targetPointModel = _pointModels.begin();
			_targetPointMark = _pointMarks.begin();
		}
		else {
			_targetPoint++;
			_targetPointModel++;
			_targetPointMark++;
		}
		_arrow.setPosition((*_targetPoint)->getPosition());
		_target.setPosition((*_targetPoint)->getPosition());
		break;
	case E_ObjectType::Plane:
		if (_targetPlane == _map.getPlanesEnd() || _targetPlane == --_map.getPlanesEnd()) {
			_targetPlane = _map.getPlanesBegin();
			_targetPlaneMark = _planeMarks.begin();
		}
		else {
			_targetPlane++;
			_targetPlaneMark++;
		}
		_arrow.setPosition((*_targetPlane)->getPosition());
		_target.setPosition((*_targetPlane)->getPosition());
		break;
	case E_ObjectType::Speaker:
		if (_targetSpeaker == _speakerMap.getPointsEnd() || _targetSpeaker == --_speakerMap.getPointsEnd()) {
			_targetSpeaker = _speakerMap.getPointsBegin();
			_targetSpeakerModel = _speakerModels.begin();
			_targetSpeakerMark = _speakerMarks.begin();
		}
		else {
			_targetSpeaker++;
			_targetSpeakerModel++;
			_targetSpeakerMark++;
		}
		_arrow.setPosition((*_targetSpeaker)->getPosition());
		_target.setPosition((*_targetSpeaker)->getPosition());
		break;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
}
void Scene::targetPrevious() {
	switch (_actualMode) {
	case E_ObjectType::Point:
		if (_targetPoint == _map.getPointsBegin()) {
			_targetPoint = _map.getPointsEnd();
			_targetPointModel = _pointModels.end();
			_targetPointMark = _pointMarks.end();
		}
		_targetPoint--;
		_targetPointModel--;
		_targetPointMark--;
		_arrow.setPosition((*_targetPoint)->getPosition());
		_target.setPosition((*_targetPoint)->getPosition());
		break;
	case E_ObjectType::Plane:
		if (_targetPlane == _map.getPlanesBegin()) {
			_targetPlane = _map.getPlanesEnd();
			_targetPlaneMark = _planeMarks.end();
		}
		_targetPlane--;
		_targetPlaneMark--;
		_arrow.setPosition((*_targetPlane)->getPosition());
		_target.setPosition((*_targetPlane)->getPosition());
		break;
	case E_ObjectType::Speaker:
		if (_targetSpeaker == _speakerMap.getPointsBegin()) {
			_targetSpeaker = _speakerMap.getPointsEnd();
			_targetSpeakerModel = _speakerModels.end();
			_targetSpeakerMark = _speakerMarks.end();
		}
		_targetSpeaker--;
		_targetSpeakerModel--;
		_targetSpeakerMark--;
		_arrow.setPosition((*_targetSpeaker)->getPosition());
		_target.setPosition((*_targetSpeaker)->getPosition());
		break;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
}
void Scene::markUnmarkAll() {
	switch (_actualMode) {
	case E_ObjectType::Point:
	{
		std::list<Model *>::iterator previousTargetPointModel = _targetPointModel;
		_targetPointModel = _pointModels.begin();
		std::list<bool>::iterator previousTargetPointMark = _targetPointMark;
		_targetPointMark = _pointMarks.begin();
		if (_numberOfPointMarks == _map.getNumberOFPoints()) {
			while (_targetPointMark != _pointMarks.end()) {
				markUnmarkTarget();
				_targetPointModel++;
				_targetPointMark++;
			}
		}
		else {
			while (_targetPointMark != _pointMarks.end()) {
				if (*_targetPointMark == false) {
					markUnmarkTarget();
				}
				_targetPointModel++;
				_targetPointMark++;
			}
		}
		_targetPointModel = previousTargetPointModel;
		_targetPointMark = previousTargetPointMark;
		break;
	}
	case E_ObjectType::Plane:
	{
		std::list<Renderable *>::iterator previousTargetPlane = _targetPlane;
		_targetPlane = _map.getPlanesBegin();
		std::list<bool>::iterator previousTargetPlaneMark = _targetPlaneMark;
		_targetPlaneMark = _planeMarks.begin();
		if (_numberOfPlaneMarks == _map.getNumberOFPlanes()) {
			while (_targetPlaneMark != _planeMarks.end()) {
				markUnmarkTarget();
				_targetPlane++;
				_targetPlaneMark++;
			}
		}
		else {
			while (_targetPlaneMark != _planeMarks.end()) {
				if (*_targetPlaneMark == false) {
					markUnmarkTarget();
				}
				_targetPlane++;
				_targetPlaneMark++;
			}
		}
		_targetPlane = previousTargetPlane;
		_targetPlaneMark = previousTargetPlaneMark;
		break;
	}
	case E_ObjectType::Speaker:
	{
		std::list<Model *>::iterator previousTargetSpeakerModel = _targetSpeakerModel;
		_targetSpeakerModel = _speakerModels.begin();
		std::list<bool>::iterator previousTargetSpeakerMark = _targetSpeakerMark;
		_targetSpeakerMark = _speakerMarks.begin();
		if (_numberOfSpeakerMarks != _speakerMarks.size()) {
			while (_targetSpeakerMark != _speakerMarks.end()) {
				markUnmarkTarget();
				_targetSpeakerModel++;
				_targetSpeakerMark++;
			}
		}
		else {
			while (_targetSpeakerMark != _speakerMarks.end()) {
				if (*_targetSpeakerMark == false) {
					markUnmarkTarget();
				}
				_targetSpeakerModel++;
				_targetSpeakerMark++;
			}
		}
		_targetSpeakerModel = previousTargetSpeakerModel;
		_targetSpeakerMark = previousTargetSpeakerMark;
		break;
	}
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
}
void Scene::markUnmarkTarget() {
	switch (_actualMode) {
	case E_ObjectType::Point:
		if (*_targetPointMark == false) {
			(*_targetPointModel)->setTextureIDForAllPlanes(E_TextureID::Marked);
			_numberOfPointMarks++;
			*_targetPointMark = true;
		}
		else {
			(*_targetPointModel)->setTextureIDForAllPlanes(E_TextureID::Plane);
			_numberOfPointMarks--;
			*_targetPointMark = false;
		}
		break;
	case E_ObjectType::Plane:
		if (*_targetPlaneMark == false) {
			(*_targetPlane)->setTextureID(E_TextureID::Marked);
			_numberOfPlaneMarks++;
			*_targetPlaneMark = true;
		}
		else {
			(*_targetPlane)->setTextureID(E_TextureID::Plane);
			_numberOfPlaneMarks--;
			*_targetPlaneMark = false;
		}
		break;
	case E_ObjectType::Speaker:
		if (*_targetSpeakerMark == false) {
			(*_targetSpeakerModel)->setTextureIDForAllPlanes(E_TextureID::Marked);
			_numberOfSpeakerMarks++;
			*_targetSpeakerMark = true;
		}
		else {
			(*_targetSpeakerModel)->setTextureIDForAllPlanes(E_TextureID::Plane);
			_numberOfSpeakerMarks--;
			*_targetSpeakerMark = false;
		}
		break;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
}
void Scene::markObjects(const std::list<bool> & marks) {
	switch (_actualMode) {
	case E_ObjectType::Point:
	{
		std::list<bool>::const_iterator orderMarkIt = marks.begin();
		std::list<Model *>::iterator previousTargetPointModel = _targetPointModel;
		_targetPointModel = _pointModels.begin();
		std::list<bool>::iterator previousTargetPointMark = _targetPointMark;
		_targetPointMark = _pointMarks.begin();
		while (orderMarkIt != marks.end()) {
			if (*_targetPointMark != *orderMarkIt) {
				markUnmarkTarget();
			}
			orderMarkIt++;
			_targetPointModel++;
			_targetPointMark++;
		}
		_targetPointModel = previousTargetPointModel;
		_targetPointMark = previousTargetPointMark;
		break;
	}
	case E_ObjectType::Plane:
	{
		std::list<bool>::const_iterator orderMarkIt = marks.begin();
		std::list<Renderable *>::iterator previousTargetPlane = _targetPlane;
		_targetPlane = _map.getPlanesBegin();
		std::list<bool>::iterator previousTargetPlaneMark = _targetPlaneMark;
		_targetPlaneMark = _planeMarks.begin();
		while (orderMarkIt != marks.end()) {
			if (*_targetPlaneMark != *orderMarkIt) {
				markUnmarkTarget();
			}
			orderMarkIt++;
			_targetPlane++;
			_targetPlaneMark++;
		}
		_targetPlane = previousTargetPlane;
		_targetPlaneMark = previousTargetPlaneMark;
		break;
	}
	case E_ObjectType::Speaker:
	{
		std::list<bool>::const_iterator orderMarkIt = marks.begin();
		std::list<Model *>::iterator previousTargetSpeakerModel = _targetSpeakerModel;
		_targetSpeakerModel = _speakerModels.begin();
		std::list<bool>::iterator previousTargetSpeakerMark = _targetSpeakerMark;
		_targetSpeakerMark = _speakerMarks.begin();
		while (orderMarkIt != marks.end()) {
			if (*_targetSpeakerMark != *orderMarkIt) {
				markUnmarkTarget();
			}
			orderMarkIt++;
			_targetSpeakerModel++;
			_targetSpeakerMark++;
		}
		_targetSpeakerModel = previousTargetSpeakerModel;
		_targetSpeakerMark = previousTargetSpeakerMark;
		break;
	}
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
}

bool Scene::isObjectAlive() {
	switch (_actualMode) {
	case E_ObjectType::Point:
		if (_targetPoint == _map.getPointsEnd()) {
			return false;
		}
		return true;
	case E_ObjectType::Plane:
		if (_targetPlane == _map.getPlanesEnd()) {
			return false;
		}
		return true;
	case E_ObjectType::Speaker:
		if (_targetSpeaker == _speakerMap.getPointsEnd()) {
			return false;
		}
		return true;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		return false;
	}
}
bool Scene::isPointOrSpeakerAlive() {
	switch (_actualMode) {
	case E_ObjectType::Point:
		if (_targetPoint == _map.getPointsEnd()) {
			return false;
		}
		return true;
	case E_ObjectType::Plane:
		return false;
	case E_ObjectType::Speaker:
		if (_targetSpeaker == _speakerMap.getPointsEnd()) {
			return false;
		}
		return true;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		return false;
	}
}
bool Scene::isAtLeastOneObject() {
	switch (_actualMode) {
	case E_ObjectType::Point:
		return (_map.getNumberOFPoints() > 0);
	case E_ObjectType::Plane:
		return (_map.getNumberOFPlanes() > 0);
	case E_ObjectType::Speaker:
		return (_speakerMap.getNumberOFPoints() > 0);
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		return false;
	}
}
bool Scene::isActionAvaliable(const E_InputAction inputAction) { //TODO
	switch (inputAction) {
	case E_InputAction::SetXAxisActive:
		return (_actualActiveAxis.getAxis() != E_Axis::X);
	case E_InputAction::SetYAxisActive:
		return (_actualActiveAxis.getAxis() != E_Axis::Y);
	case E_InputAction::SetZAxisActive:
		return (_actualActiveAxis.getAxis() != E_Axis::Z);
	case E_InputAction::SetPointMode:
		return (_actualMode != E_ObjectType::Point);
	case E_InputAction::SetPlaneMode:
		return (_actualMode != E_ObjectType::Plane);
	case E_InputAction::SetSpeakerMode:
		return (_actualMode != E_ObjectType::Speaker);
	case E_InputAction::AddObject:
		switch (_actualMode) {
		case E_ObjectType::Point:
			return (_targetPoint != _map.getPointsEnd());
		case E_ObjectType::Plane:
			return (_numberOfPointMarks > 2 && _numberOfPointMarks < 5);
		case E_ObjectType::Speaker:
			return (_targetSpeaker != _speakerMap.getPointsEnd());
		default:
			std::cout << "Error: Unsupported mode!" << std::endl;
			return false;
		}
	case E_InputAction::DeleteObject:
		return isObjectAlive();
	case E_InputAction::MoveFurther:
		return isPointOrSpeakerAlive();
	case E_InputAction::MoveCloser:
		return isPointOrSpeakerAlive();
	case E_InputAction::TargetNext:
		isAtLeastOneObject();
	case E_InputAction::TargetPrevious:
		isAtLeastOneObject();
	case E_InputAction::SaveFiles:
		return true;
	case E_InputAction::LoadFiles:
		return true; //TODO: ask if to save
	case E_InputAction::Undo:
		return true;
	case E_InputAction::Redo:
		return true;
	case E_InputAction::MarkAllObjects:
		return true;
	case E_InputAction::MarkObject:
		return isObjectAlive();
	case E_InputAction::ExitApp:
		return true; //TODO: ask if to save
	default:
		std::cout << "Error: Unsupported input action!" << std::endl;
		break;
	}
	return false;
}
void Scene::sendAction(const E_InputAction inputAction) {
	switch (inputAction) {
	case E_InputAction::SetXAxisActive:
		_actionManager->executeAction(Action(E_ActionType::SetActiveAxis,
			_actualActiveAxis,
			Axis(E_Axis::X)));
		return;
	case E_InputAction::SetYAxisActive:
		_actionManager->executeAction(Action(E_ActionType::SetActiveAxis,
			_actualActiveAxis,
			Axis(E_Axis::Y)));
		return;
	case E_InputAction::SetZAxisActive:
		_actionManager->executeAction(Action(E_ActionType::SetActiveAxis,
			_actualActiveAxis,
			Axis(E_Axis::Z)));
		return;
	case E_InputAction::SetPointMode:
		_actionManager->executeAction(Action(E_ActionType::SetActiveMode,
			_actualMode,
			E_ObjectType::Point,
			_pointMarks));
		return;
	case E_InputAction::SetPlaneMode:
		_actionManager->executeAction(Action(E_ActionType::SetActiveMode,
			_actualMode,
			E_ObjectType::Plane,
			_planeMarks));
		return;
	case E_InputAction::SetSpeakerMode:
		_actionManager->executeAction(Action(E_ActionType::SetActiveMode,
			_actualMode,
			E_ObjectType::Speaker,
			_speakerMarks));
		return;
	case E_InputAction::AddObject:
		switch (_actualMode) {
		case E_ObjectType::Point:
			_actionManager->executeAction(Action(E_ActionType::AddPoint,
				(*_targetPoint)->getPosition()));
			return;
		case E_ObjectType::Plane:
			_actionManager->executeAction(Action(E_ActionType::AddPlane,
				_pointMarks));
			return;
		case E_ObjectType::Speaker:
			_actionManager->executeAction(Action(E_ActionType::AddSpeaker,
				(*_targetSpeaker)->getPosition()));
			return;
		default:
			std::cout << "Error: Unsupported mode!" << std::endl;
			return;
		}
	case E_InputAction::DeleteObject:
		std::cout << "Error: Unsupported action!" << std::endl; //TODO
		return;
	case E_InputAction::MoveFurther:
		switch (_actualActiveAxis.getAxis()) {
		case E_Axis::X:
			_actionManager->executeAction(Action(E_ActionType::MoveObject,
				Vector3f(_OBJECT_MOVE_SPEED, 0.f, 0.f)));
			return;
		case E_Axis::Y:
			_actionManager->executeAction(Action(E_ActionType::MoveObject,
				Vector3f(0.f, _OBJECT_MOVE_SPEED, 0.f)));
			return;
		case E_Axis::Z:
			_actionManager->executeAction(Action(E_ActionType::MoveObject,
				Vector3f(0.f, 0.f, _OBJECT_MOVE_SPEED)));
			return;
		default:
			std::cout << "Error: Unsupported axis!" << std::endl;
			return;
		}
	case E_InputAction::MoveCloser:
		switch (_actualActiveAxis.getAxis()) {
		case E_Axis::X:
			_actionManager->executeAction(Action(E_ActionType::MoveObject,
				Vector3f(-_OBJECT_MOVE_SPEED, 0.f, 0.f)));
			return;
		case E_Axis::Y:
			_actionManager->executeAction(Action(E_ActionType::MoveObject,
				Vector3f(0.f, -_OBJECT_MOVE_SPEED, 0.f)));
			return;
		case E_Axis::Z:
			_actionManager->executeAction(Action(E_ActionType::MoveObject,
				Vector3f(0.f, 0.f, -_OBJECT_MOVE_SPEED)));
			return;
		default:
			std::cout << "Error: Unsupported axis!" << std::endl;
			return;
		}
	case E_InputAction::TargetNext:
		_actionManager->executeAction(Action(E_ActionType::TargetNext));
		return;
	case E_InputAction::TargetPrevious:
		_actionManager->executeAction(Action(E_ActionType::TargetPrevious));
		return;
	case E_InputAction::SaveFiles:
		std::cout << "Error: Unsupported action!" << std::endl; //TODO
		return;
	case E_InputAction::LoadFiles:
		std::cout << "Error: Unsupported action!" << std::endl; //TODO
		return;
	case E_InputAction::Undo:
		_actionManager->undo();
		return;
	case E_InputAction::Redo:
		_actionManager->redo();
		return;
	case E_InputAction::MarkAllObjects:
		switch (_actualMode) {
		case E_ObjectType::Point:
			_actionManager->executeAction(Action(E_ActionType::MarkAll,
				_pointMarks));
			return;
		case E_ObjectType::Plane:
			_actionManager->executeAction(Action(E_ActionType::MarkAll,
				_planeMarks));
			return;
		case E_ObjectType::Speaker:
			_actionManager->executeAction(Action(E_ActionType::MarkAll,
				_speakerMarks));
			return;
		default:
			std::cout << "Error: Unsupported mode!" << std::endl;
			return;
		}
	case E_InputAction::MarkObject:
		_actionManager->executeAction(Action(E_ActionType::Mark));
		return;
	case E_InputAction::ExitApp:
		//TODO
		return;
	default:
		std::cout << "Error: Unsupported input action!" << std::endl;
		return;
	}
}

Scene::Scene()
	: _OBJECT_MOVE_SPEED(0.01f),
	_actualMode(Point), _actualActiveAxis(E_Axis::X),
	_targetPoint(_map.getPointsEnd()), _targetPointModel(_pointModels.end()), _targetPointMark(_pointMarks.end()),
	_targetPlane(_map.getPlanesEnd()), _targetPlaneMark(_planeMarks.end()),
	_numberOfPointMarks(0), _numberOfPlaneMarks(0), _numberOfSpeakerMarks(0),
	_targetSpeaker(_speakerMap.getPointsEnd()), _targetSpeakerModel(_speakerModels.end()), _targetSpeakerMark(_speakerMarks.end())
{
	_actionManager = new ActionManager(*this);

	_map.loadModelFromFile("Models/map");
	for (const ModelPoint * mapPoint : _map.getPoints()) {
		Model * point = new Model();
		point->loadModelFromFile("Models/point");
		point->setPosition(mapPoint->getPosition());
		point->setScale(Vector3f(0.02f, 0.02f, 0.02f));
		point->setIfAutoscaled(true);
		_pointModels.push_back(point);
		_pointMarks.push_back(false);
	}
	for (const Renderable * mapPlane : _map.getPlanes()) {
		_planeMarks.push_back(false);
	}

	_speakerMap.loadModelFromFile("Models/speakerMap");
	for (const ModelPoint * speakerMapPoint : _speakerMap.getPoints()) {
		Model * speaker = new Model();
		speaker->loadModelFromFile("Models/speaker");
		speaker->setPosition(speakerMapPoint->getPosition());
		speaker->setScale(Vector3f(0.02f, 0.02f, 0.02f));
		speaker->setIfAutoscaled(true);
		_speakerModels.push_back(speaker);
		_speakerMarks.push_back(false);
	}

	_arrow.loadModelFromFile("Models/arrow");
	_arrow.setScale(Vector3f(0.05f, 0.05f, 0.05f));
	_arrow.setIfAutoscaled(true);
	_target.loadModelFromFile("Models/target");
	_target.setScale(Vector3f(0.03f, 0.03f, 0.03f));
	_target.setIfAutoscaled(true);
	_target.setIfAutorotated(true);
}
const std::list<const Model *> & Scene::getModels() {
	_models.clear();
	_models.push_back(&_map);
	_models.insert(_models.end(), _pointModels.begin(), _pointModels.end());
	_models.insert(_models.end(), _speakerModels.begin(), _speakerModels.end());
	switch (_actualMode) {
	case E_ObjectType::Point:
		if (_targetPoint != _map.getPointsEnd()) {
			_models.push_back(&_arrow);
			_models.push_back(&_target);
		}
		break;
	case E_ObjectType::Plane:
		if (_targetPlane != _map.getPlanesEnd()) {
			_models.push_back(&_arrow);
			_models.push_back(&_target);
		}
		break;
	case E_ObjectType::Speaker:
		if (_targetSpeaker != _speakerMap.getPointsEnd()) {
			_models.push_back(&_arrow);
			_models.push_back(&_target);
		}
		break;
	default:
		std::cout << "Error: Unsupported mode!" << std::endl;
		break;
	}
	return _models;
}
void Scene::update(float deltaTime) {
	for (Model * point : _pointModels) {
		point->rotate(1.f);
	}
}
void Scene::orderAction(const E_InputAction inputAction) {
	if (isActionAvaliable(inputAction)) {
		sendAction(inputAction);
	}
}
Scene::~Scene() {
	delete _actionManager;
	for (Model * pointModel : _pointModels) {
		delete pointModel;
	}
	for (Model * speakerModel : _speakerModels) {
		delete speakerModel;
	}
}