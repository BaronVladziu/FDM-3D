#pragma once

enum class E_ActionType {
	SetActiveAxis, //2*enum
	SetActiveMode, //2*enum + IDs
	AddPoint, //ID + position
	AddPlane, //(x+1)*ID
	AddSpeaker, //ID + position
	DeletePoint, //ID + position
	DeletePlane, //(x+1)*ID
	DeleteSpeaker, //ID + position
	MoveObject, //enum + ID + vector
	TargetNext, //enum + ID
	TargetPrevious, //enum + ID
	MarkAll, //IDs
	Mark, //enum + ID
	Unmark //enum + ID
};