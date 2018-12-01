//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_RENDERTRIANGLE_H
#define VULKAN_FDM_RENDERTRIANGLE_H

#include "header.h"
#include "RenderVertex.h"
#include "TextureType.h"
#include "ComplexFloat.h"


class RenderTriangle {

    TextureType _textureID;
    std::list<RenderVertex> _vertices;
    ComplexFloat _value;

public:
    RenderTriangle(TextureType textureID, RenderVertex v1, RenderVertex v2, RenderVertex v3);
    RenderTriangle(TextureType textureID, RenderVertex v1, RenderVertex v2, RenderVertex v3, ComplexFloat value);
    const TextureType getTexID() const;
    const ComplexFloat & getValue() const;
    const std::list<RenderVertex> & getVertices() const;

private:
    void initialize(TextureType textureID, RenderVertex & v1, RenderVertex & v2, RenderVertex & v3);

};


#endif //VULKAN_FDM_RENDERTRIANGLE_H
