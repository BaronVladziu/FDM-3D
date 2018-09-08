//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_RENDERTRIANGLE_H
#define VULKAN_FDM_RENDERTRIANGLE_H

#include "header.h"
#include "RenderVertex.h"


class RenderTriangle {

    std::vector<RenderVertex> _vertices;

public:
    RenderTriangle(RenderVertex v1, RenderVertex v2, RenderVertex v3);
    const std::vector<RenderVertex> & getVertices() const;

};


#endif //VULKAN_FDM_RENDERTRIANGLE_H
