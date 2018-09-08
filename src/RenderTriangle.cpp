//
// Created by baronvladziu on 08.09.18.
//

#include "RenderTriangle.h"


RenderTriangle::RenderTriangle(RenderVertex v1, RenderVertex v2, RenderVertex v3)
    : _vertices{v1, v2, v3}
{}
const std::vector<RenderVertex> & RenderTriangle::getVertices() const {
    return _vertices;
}
