//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_MAP_H
#define VULKAN_FDM_MAP_H

#include "header.h"
#include "RenderTriangle.h"


class Map {

    std::vector<RenderTriangle> _triangles;

public:
    void addRenderTriange(const RenderTriangle & triangle);
    const std::vector<RenderTriangle> & getRenderTriangles() const;

};


#endif //VULKAN_FDM_MAP_H
