//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_SOLVER_H
#define VULKAN_FDM_SOLVER_H

#include "header.h"
#include "Map.h"
#include "SolverPoint.h"
#include "Complex2RealType.h"
#include "ScaleType.h"
#include "DimensionName.h"
#include "JacobiSystemOfEquations.h"
#include "SolverConfiguration.h"


class Solver {

    constexpr static float _SOUND_SPEED = 340.f;
//    constexpr static float _DENSITY_OF_AIR = 1.225f;
//    constexpr static float _PLANE_WAVE_IMPEDANCE = _DENSITY_OF_AIR*_SOUND_SPEED;
    constexpr static float _PI() { return float(std::atan(1)*4); };
    constexpr static float _REFERENCE_PRESSURE = 0.00002f;

    constexpr static float _ARROW_SIZE = 0.03f;

    constexpr static int _NUMBER_OF_THIRD_OCTAVE_BANDS = 45;
    constexpr static float _THIRD_OCTAVE_BANDS[_NUMBER_OF_THIRD_OCTAVE_BANDS] =
            {1, 1.25f, 1.6f, 2, 2.5f, 3.15f, 4, 5, 6.3f, 8,
             10, 12.5f, 16, 20, 25, 31.5f, 40, 50, 63, 80,
             100, 125, 160, 200, 250, 315, 400, 500, 630, 800,
             1000, 1250, 1600, 2000, 2500, 3150, 4000, 5000, 6300, 8000,
             10000, 12500, 16000, 20000, 25000};
    constexpr static int _NUMBER_OF_OCTAVE_BANDS = 15;
    constexpr static float _OCTAVE_BANDS[_NUMBER_OF_OCTAVE_BANDS] =
            {1, 2, 4, 8, 16, 31.5f, 63, 125, 250, 500,
             1000, 2000, 4000, 8000, 16000};

    float _numberOfPointsPerPeriod;
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

    SolverPoint *** _grid;
    bool *** _cubeMatrix;

public:
    std::unique_ptr<std::list<RenderTriangle>> solveRoom(const Map & map, const SolverConfiguration & config);
    std::unique_ptr<std::list<RenderTriangle>> solveReceivers(const Map & map, const SolverConfiguration & config);

private:
    std::unique_ptr<std::list<RenderTriangle>> markAndCreateCubes(bool *** cubeMatrix, SolverPoint *** grid,
            const std::list<RenderTriangle> & trianglesToCube, TextureType textureID, bool isSource) const;
    std::list<glm::ivec3> findCubesOnLine(const glm::ivec3 & point1, const glm::ivec3 & point2) const;
    JacobiSystemOfEquations createSystemOfEquations(SolverPoint *** grid) const;
    int calculateVariableIndex(int i, int j, int k, bool b) const;
    int pseudoSignum(float x) const;
    float max(float x, float y, float z) const;
    void setBorder(JacobiSystemOfEquations & systemOfEquations, int actRealID, int actImagID,
            int neiRealID, int neiImagID, float constant) const;
    void setBorderX(JacobiSystemOfEquations & systemOfEquations, int actRealID, int actImagID,
            int i, int j, int k) const;
    void setBorderY(JacobiSystemOfEquations & systemOfEquations, int actRealID, int actImagID,
                    int i, int j, int k) const;
    void setBorderZ(JacobiSystemOfEquations & systemOfEquations, int actRealID, int actImagID,
                    int i, int j, int k) const;
    void createGrid(const Map & map, float frequency, int minNumberOfPointsPerPeriod);
    void deleteGrid() const;
    std::unique_ptr<std::list<RenderTriangle>> createSolutionTriangles(const JacobiSystemOfEquations & equations,
            const SolverConfiguration & config, const std::list<RenderTriangle> & wallTriangles,
            const std::list<RenderTriangle> & speakerTriangles) const;

};


#endif //VULKAN_FDM_SOLVER_H
