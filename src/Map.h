//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_MAP_H
#define VULKAN_FDM_MAP_H

#include "header.h"
#include "RenderTriangle.h"


class Map {

    std::list<RenderTriangle> _wallTriangles;
    std::list<RenderTriangle> _speakerTriangles;

public:
    void addWallTriange(const RenderTriangle & triangle);
    const std::list<RenderTriangle> & getWallTriangles() const;
    void addSpeakerTriange(const RenderTriangle & triangle);
    const std::list<RenderTriangle> & getSpeakerTriangles() const;

};


#endif //VULKAN_FDM_MAP_H
