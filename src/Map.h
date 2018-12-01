//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_MAP_H
#define VULKAN_FDM_MAP_H

#include "header.h"
#include "RenderTriangle.h"
#include "Range3D.h"


class Map {

    Range3D _ranges;
    std::list<RenderTriangle> _wallTriangles;
    std::list<RenderTriangle> _speakerTriangles;
    std::list<RenderVertex> _receivers;

public:
    void setRanges(const Range3D & range);
    void setMins(float minX, float minY, float minZ);
    void setMaxes(float maxX, float maxY, float maxZ);
    float getMinX() const;
    float getMinY() const;
    float getMinZ() const;
    float getMaxX() const;
    float getMaxY() const;
    float getMaxZ() const;
    void addWallTriange(const RenderTriangle & triangle);
    const std::list<RenderTriangle> & getWallTriangles() const;
    void addSpeakerTriange(const RenderTriangle & triangle);
    const std::list<RenderTriangle> & getSpeakerTriangles() const;
    void addReceiver(const RenderVertex & vertex);
    const std::list<RenderVertex> & getReceivers() const;

};


#endif //VULKAN_FDM_MAP_H
