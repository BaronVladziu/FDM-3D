//
// Created by baronvladziu on 08.09.18.
//

#include "Map.h"


void Map::setRanges(const Range3D & range) {
    _ranges = range;
}
void Map::setMins(float minX, float minY, float minZ) {
    _ranges.setMinX(minX);
    _ranges.setMinY(minY);
    _ranges.setMinZ(minZ);
}
void Map::setMaxes(float maxX, float maxY, float maxZ) {
    _ranges.setMaxX(maxX);
    _ranges.setMaxY(maxY);
    _ranges.setMaxZ(maxZ);
}
float Map::getMinX() const {
    return _ranges.getMinX();
}
float Map::getMinY() const {
    return _ranges.getMinY();
}
float Map::getMinZ() const {
    return _ranges.getMinZ();
}
float Map::getMaxX() const {
    return _ranges.getMaxX();
}
float Map::getMaxY() const {
    return _ranges.getMaxY();
}
float Map::getMaxZ() const {
    return _ranges.getMaxZ();
}
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
void Map::addReceiver(const RenderVertex & vertex) {
    _receivers.push_back(vertex);
}
const std::list<RenderVertex> & Map::getReceivers() const {
    return _receivers;
}
