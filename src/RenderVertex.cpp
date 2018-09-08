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
