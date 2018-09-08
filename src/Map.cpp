//
// Created by baronvladziu on 08.09.18.
//

#include "Map.h"


void Map::addRenderTriange(const RenderTriangle & triangle) {
    _triangles.push_back(triangle);
}
const std::vector<RenderTriangle> & Map::getRenderTriangles() const {
    return _triangles;
}
