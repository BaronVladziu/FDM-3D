//
// Created by baronvladziu on 21.11.18.
//

#include "Range3D.h"


Range3D::Range3D(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
    : _minX(minX), _minY(minY), _minZ(minZ), _maxX(maxX), _maxY(maxY), _maxZ(maxZ)
{}
float Range3D::getMaxX() const {
    return _maxX;
}
float Range3D::getMaxY() const {
    return _maxY;
}
float Range3D::getMaxZ() const {
    return _maxZ;
}
float Range3D::getMinX() const {
    return _minX;
}
float Range3D::getMinY() const {
    return _minY;
}
float Range3D::getMinZ() const {
    return _minZ;
}
void Range3D::setMaxX(float v) {
    _maxX = v;
}
void Range3D::setMaxY(float v) {
    _maxY = v;
}
void Range3D::setMaxZ(float v) {
    _maxZ = v;
}
void Range3D::setMinX(float v) {
    _minX = v;
}
void Range3D::setMinY(float v) {
    _minY = v;
}
void Range3D::setMinZ(float v) {
    _minZ = v;
}
Range3D Range3D::operator+(const Range3D & range) const {
    Range3D result;
    result._minX = min(_minX, range._minX);
    result._minY = min(_minY, range._minY);
    result._minZ = min(_minZ, range._minZ);
    result._maxX = max(_maxX, range._maxX);
    result._maxY = max(_maxY, range._maxY);
    result._maxZ = max(_maxZ, range._maxZ);
    return result;
}
Range3D & Range3D::operator=(const Range3D & range) {
    _minX = range._minX;
    _minY = range._minY;
    _minZ = range._minZ;
    _maxX = range._maxX;
    _maxY = range._maxY;
    _maxZ = range._maxZ;
}
void Range3D::operator+=(const Range3D & range) {
    _minX = min(_minX, range._minX);
    _minY = min(_minY, range._minY);
    _minZ = min(_minZ, range._minZ);
    _maxX = max(_maxX, range._maxX);
    _maxY = max(_maxY, range._maxY);
    _maxZ = max(_maxZ, range._maxZ);
}

float Range3D::min(float a, float b) const {
    if (a > b) return b;
    else return a;
}
float Range3D::max(float a, float b) const {
    if (a > b) return a;
    else return b;
}
