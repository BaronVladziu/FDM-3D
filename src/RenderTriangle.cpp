//
// Created by baronvladziu on 08.09.18.
//

#include "RenderTriangle.h"


RenderTriangle::RenderTriangle(TextureType textureID, RenderVertex v1, RenderVertex v2, RenderVertex v3)
{
    initialize(textureID, v1, v2, v3);
}
RenderTriangle::RenderTriangle(TextureType textureID, RenderVertex v1, RenderVertex v2, RenderVertex v3, ComplexFloat value)
    : _value(value)
{
    initialize(textureID, v1, v2, v3);
}
const TextureType RenderTriangle::getTexID() const {
    return _textureID;
}
const ComplexFloat & RenderTriangle::getValue() const {
    return _value;
}
const std::list<RenderVertex> & RenderTriangle::getVertices() const {
    return _vertices;
}

void RenderTriangle::initialize(TextureType textureID, RenderVertex & v1, RenderVertex & v2, RenderVertex & v3) {
    _textureID = textureID;
    switch (_textureID) {
        case WALL: {
            v1.setTexPosition(v1.getTexX() / 2, v1.getTexY() / 2);
            v2.setTexPosition(v2.getTexX() / 2, v2.getTexY() / 2);
            v3.setTexPosition(v3.getTexX() / 2, v3.getTexY() / 2);
            break;
        }
        case SPEAKER: {
            if (_value == ComplexFloat(0.f, 0.f)) {
                std::cout << "Warning: Created speaker with no volume!" << std::endl;
            }
            v1.setTexPosition(v1.getTexX() / 2 + 0.5f, v1.getTexY() / 2);
            v2.setTexPosition(v2.getTexX() / 2 + 0.5f, v2.getTexY() / 2);
            v3.setTexPosition(v3.getTexX() / 2 + 0.5f, v3.getTexY() / 2);
            break;
        }
        case WHITE: {
            v1.setTexPosition(v1.getTexX() / 2, v1.getTexY() / 2 + 0.5f);
            v2.setTexPosition(v2.getTexX() / 2, v2.getTexY() / 2 + 0.5f);
            v3.setTexPosition(v3.getTexX() / 2, v3.getTexY() / 2 + 0.5f);
            break;
        }
        case COLOR: {
            v1.setTexPosition(v1.getTexX() / 2 + 0.5f, v1.getTexY() / 2 + 0.5f);
            v2.setTexPosition(v2.getTexX() / 2 + 0.5f, v2.getTexY() / 2 + 0.5f);
            v3.setTexPosition(v3.getTexX() / 2 + 0.5f, v3.getTexY() / 2 + 0.5f);
            break;
        }
        default: {
            std::cout << "Unknown texture!" << std::endl;
            break;
        }
    }
    _vertices.emplace_back(v1);
    _vertices.emplace_back(v2);
    _vertices.emplace_back(v3);
}
