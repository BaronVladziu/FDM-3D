//
// Created by baronvladziu on 08.09.18.
//

#include "Map.h"


void Map::addWallTriange(const RenderTriangle & triangle) {
    _wallTriangles.push_back(triangle);
}
const std::list<RenderTriangle> & Map::getWallTriangles() const {
    return _wallTriangles;
}
void Map::addSpeakerTriange(const RenderTriangle & triangle) {
    _speakerTriangles.push_back(triangle);
}
const std::list<RenderTriangle> & Map::getSpeakerTriangles() const {
    return _speakerTriangles;
}
