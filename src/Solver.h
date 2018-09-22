//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_SOLVER_H
#define VULKAN_FDM_SOLVER_H

#include "header.h"
#include "Map.h"
#include "SolverPoint.h"
#include "SystemOfEquations.h"


class Solver {

    constexpr static float _SOUND_SPEED = 340.f;
    constexpr static float _DENSITY_OF_AIR = 1.225f;
    constexpr static float _PLANE_WAVE_IMPEDANCE = _DENSITY_OF_AIR*_SOUND_SPEED;
    constexpr static float _PI() { return float(std::atan(1)*4); };
    constexpr static int _NUMBER_OF_POINTS_PER_PERIOD = 6;

    float _edgeLength;
    float _angularFrequency;
    float _waveLength;
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
    std::list<RenderTriangle> markAndCreateCubes(bool *** cubeMatrix, SolverPoint *** grid,
            const std::list<RenderTriangle> & trianglesToCube, TextureType textureID, bool isSource) const;
    std::list<glm::ivec3> findCubesOnLine(const glm::ivec3 & point1, const glm::ivec3 & point2) const;
    SystemOfEquations createSystemOfEquations(SolverPoint *** grid) const;
    int calculateVariableIndex(int i, int j, int k, int c) const;
    int pseudoSignum(float x) const;
    float max(float x, float y, float z) const;

};


#endif //VULKAN_FDM_SOLVER_H
