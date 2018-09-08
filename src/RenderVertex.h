//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_RENDERVERTEX_H
#define VULKAN_FDM_RENDERVERTEX_H

#include "header.h"


class RenderVertex {

    float _posX;
    float _posY;
    float _posZ;
    float _texX;
    float _texY;

public:
    RenderVertex(float x, float y, float z, float textureX, float textureY);
    float getX() const;
    float getY() const;
    float getZ() const;
    float getTexX() const;
    float getTexY() const;

};


#endif //VULKAN_FDM_RENDERVERTEX_H
