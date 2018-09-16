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
    RenderVertex() = default;
    RenderVertex(float x, float y, float z, float textureX, float textureY);
    float getX() const;
    float getY() const;
    float getZ() const;
    float getTexX() const;
    float getTexY() const;
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setTexX(float textureX);
    void setTexY(float textureY);
    void setPosition(const glm::vec3 & position);
    void setTexPosition(float textureX, float textureY);

};


#endif //VULKAN_FDM_RENDERVERTEX_H
