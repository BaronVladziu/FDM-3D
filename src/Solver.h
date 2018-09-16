//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_SOLVER_H
#define VULKAN_FDM_SOLVER_H

#include "header.h"
#include "Map.h"


class Solver {

    constexpr static float _SOUND_SPEED = 340.f;
    constexpr static int _NUMBER_OF_POINTS_PER_PERIOD = 6;

    float _edgeLength;
    int _pointMatrixSizeX;
    int _pointMatrixSizeY;
    int _pointMatrixSizeZ;
    float _minX;
    float _minY;
    float _minZ;
    float _maxX;
    float _maxY;
    float _maxZ;

public:
    std::list<RenderTriangle> solveRoom(const Map & map, float frequency);

private:
    std::list<RenderTriangle> markAndCreateCubes(bool *** cubeMatrix,
            const std::list<RenderTriangle> & trianglesToCube, TextureType textureID) const;
    std::list<glm::ivec3> findCubesOnLine(const glm::ivec3 & point1, const glm::ivec3 & point2) const;

};


#endif //VULKAN_FDM_SOLVER_H
