#include "Axis.h"

Axis::Axis()
{}
Axis::Axis(E_Axis axis)
	: _axis(axis)
{}
E_Axis Axis::getAxis() const {
	return _axis;
}
char Axis::getName() const {
	switch (_axis) {
	case X:
		return 'X';
	case Y:
		return 'Y';
	case Z:
		return 'Z';
	default:
		std::cout << "Error: Unsupported axis" << std::endl;
		return '_';
	}
}
Vector3f Axis::getVector() const {
	switch (_axis) {
	case X:
		return Vector3f(1.f, 0.f, 0.f);
	case Y:
		return Vector3f(0.f, 1.f, 0.f);
	case Z:
		return Vector3f(0.f, 0.f, 1.f);
	default:
		std::cout << "Error: Unsupported axis" << std::endl;
		return Vector3f(0.f, 0.f, 0.f);
	}
}
Axis::~Axis()
{}