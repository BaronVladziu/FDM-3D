//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_RENDERTRIANGLE_H
#define VULKAN_FDM_RENDERTRIANGLE_H

#include "header.h"
#include "RenderVertex.h"
#include "TextureType.h"


class RenderTriangle {

    TextureType _textureID;
    std::list<RenderVertex> _vertices;

public:
    RenderTriangle(TextureType textureID, RenderVertex v1, RenderVertex v2, RenderVertex v3);
    const TextureType getTexID() const;
    const std::list<RenderVertex> & getVertices() const;

};


#endif //VULKAN_FDM_RENDERTRIANGLE_H
