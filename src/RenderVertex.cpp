//
// Created by baronvladziu on 08.09.18.
//

#include "RenderVertex.h"


RenderVertex::RenderVertex(float x, float y, float z, float textureX, float textureY)
    : _posX(x), _posY(y), _posZ(z), _texX(textureX), _texY(textureY)
{}
float RenderVertex::getX() const {
    return _posX;
}
float RenderVertex::getY() const {
    return _posY;
}
float RenderVertex::getZ() const {
    return _posZ;
}
float RenderVertex::getTexX() const {
    return _texX;
}
float RenderVertex::getTexY() const {
    return _texY;
}
void RenderVertex::setX(float x) {
    _posX = x;
}
void RenderVertex::setY(float y) {
    _posY = y;
}
void RenderVertex::setZ(float z) {
    _posZ = z;
}
void RenderVertex::setTexX(float textureX) {
    _texX = textureX;
}
void RenderVertex::setTexY(float textureY) {
    _texY = textureY;
}
void RenderVertex::setPosition(const glm::vec3 & position) {
    _posX = position.x;
    _posY = position.y;
    _posZ = position.z;
}
void RenderVertex::setTexPosition(float textureX, float textureY) {
    _texX = textureX;
    _texY = textureY;
}
