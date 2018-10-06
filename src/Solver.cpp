//
// Created by baronvladziu on 08.09.18.
//

#include "Solver.h"


//public:
std::list<RenderTriangle> Solver::solveRoom(const Map & map, float frequency) {
    //--- CREATE GRID ---//
    //Prepare triangles
    const std::list<RenderTriangle> & wallTriangles = map.getWallTriangles();
    const std::list<RenderTriangle> & speakerTriangles = map.getSpeakerTriangles();
    //Get first vertex
    const RenderVertex & firstVertex = *(speakerTriangles.begin()->getVertices().begin());
    //Find mins and maxs for grid
    _minX = firstVertex.getX();
    _minY = firstVertex.getY();
    _minZ = firstVertex.getZ();
    _maxX = firstVertex.getX();
    _maxY = firstVertex.getY();
    _maxZ = firstVertex.getZ();
    for (const RenderTriangle & renT : wallTriangles) {
        for (const RenderVertex & renV : renT.getVertices()) {
            if (renV.getX() < _minX) { _minX = renV.getX(); }
            if (renV.getX() > _maxX) { _maxX = renV.getX(); }
            if (renV.getY() < _minY) { _minY = renV.getY(); }
            if (renV.getY() > _maxY) { _maxY = renV.getY(); }
            if (renV.getZ() < _minZ) { _minZ = renV.getZ(); }
            if (renV.getZ() > _maxZ) { _maxZ = renV.getZ(); }
        }
    }
    for (const RenderTriangle & renT : speakerTriangles) {
        for (const RenderVertex & renV : renT.getVertices()) {
            if (renV.getX() < _minX) { _minX = renV.getX(); }
            if (renV.getX() > _maxX) { _maxX = renV.getX(); }
            if (renV.getY() < _minY) { _minY = renV.getY(); }
            if (renV.getY() > _maxY) { _maxY = renV.getY(); }
            if (renV.getZ() < _minZ) { _minZ = renV.getZ(); }
            if (renV.getZ() > _maxZ) { _maxZ = renV.getZ(); }
        }
    }
    //Calculate constants
    _edgeLength = _SOUND_SPEED / (_NUMBER_OF_POINTS_PER_PERIOD*frequency);
    _angularFrequency = 2.f*_PI()*frequency;
    _waveLength = _angularFrequency/_SOUND_SPEED;
    std::cout << "Edge length: " << _edgeLength << std::endl;
    //Create 3d point matrix
    _pointMatrixSizeX = int((_maxX - _minX) / _edgeLength) + 1;
    _pointMatrixSizeY = int((_maxY - _minY) / _edgeLength) + 1;
    _pointMatrixSizeZ = int((_maxZ - _minZ) / _edgeLength) + 1;
    std::cout << "Grid size: " << _pointMatrixSizeX << " - " << _pointMatrixSizeY << " - " << _pointMatrixSizeZ << std::endl;
    SolverPoint *** grid = new SolverPoint ** [_pointMatrixSizeX + 1];
    for (int i = 0; i < _pointMatrixSizeX + 1; i++) {
        grid[i] = new SolverPoint * [_pointMatrixSizeY + 1];
        for (int j = 0; j < _pointMatrixSizeY + 1; j++) {
            grid[i][j] = new SolverPoint[_pointMatrixSizeZ + 1];
        }
    }
    //Create cube matrix
    bool *** cubeMatrix = new bool ** [_pointMatrixSizeX];
    for (int i = 0; i < _pointMatrixSizeX; i++) {
        cubeMatrix[i] = new bool * [_pointMatrixSizeY];
        for (int j = 0; j < _pointMatrixSizeY; j++) {
            cubeMatrix[i][j] = new bool[_pointMatrixSizeZ];
            for (int k = 0; k < _pointMatrixSizeZ; k++) {
                cubeMatrix[i][j][k] = false;
            }
        }
    }

    //--- SET WALLS---//
    std::list<RenderTriangle> cubeTriangles = markAndCreateCubes(cubeMatrix, grid, wallTriangles, TextureType::WALL, false);
    std::list<RenderTriangle> cubesSpeakerTriangles = markAndCreateCubes(cubeMatrix, grid, speakerTriangles, TextureType::SPEAKER, true);
    cubeTriangles.insert(cubeTriangles.end(), cubesSpeakerTriangles.begin(), cubesSpeakerTriangles.end());

    //--- CREATE EQUATIONS ---//
    MatrixSystemOfEquations equations = createSystemOfEquations(grid);
    equations.solve(100);

    //Print equations
    std::ofstream myfile;
    myfile.open ("equations.txt");
    for (int j = 0; j < equations.getNumberOfVariables(); j++) {
        for (int i = 0; i < equations.getNumberOfVariables(); i++) {
            myfile << equations.get(i, j).real << "+" << equations.get(i, j).imag << "i\t";
        }
        myfile << equations.getConstant(j).real << "+" << equations.getConstant(j).imag << "i\t";
        myfile << std::endl;
    }
    myfile << std::endl;
    myfile.close();

    //Cleanup
    for (int i = 0; i < _pointMatrixSizeX + 1; i++) {
        for (int j = 0; j < _pointMatrixSizeY + 1; j++) {
            delete[] grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
    for (int i = 0; i < _pointMatrixSizeX; i++) {
        for (int j = 0; j < _pointMatrixSizeY; j++) {
            delete[] cubeMatrix[i][j];
        }
        delete[] cubeMatrix[i];
    }
    delete[] cubeMatrix;

    //--- CREATE SOLUTION CUBES ---//
    std::list<RenderTriangle> solutionTriangles;
    for (int ix = 0; ix < _pointMatrixSizeX; ix++) {
        for (int iy = 0; iy < _pointMatrixSizeY; iy++) {
            for (int iz = 0; iz < _pointMatrixSizeZ; iz++) {
                //Trangle corners
                glm::vec3 pointCenter = glm::vec3((ix * _edgeLength) + _minX, (iy * _edgeLength) + _minY, (iz * _edgeLength) + _minZ);
                float solutionPointRadius = 0.03f;
                RenderVertex cornerXp = RenderVertex(glm::vec3(pointCenter + glm::vec3(solutionPointRadius, 0, 0)), 0.5f, 0.5f);
                RenderVertex cornerXm = RenderVertex(glm::vec3(pointCenter + glm::vec3(-solutionPointRadius, 0, 0)), 0.5f, 0.5f);
                RenderVertex cornerYp = RenderVertex(glm::vec3(pointCenter + glm::vec3(0, solutionPointRadius, 0)), 0.5f, 0.5f);
                RenderVertex cornerYm = RenderVertex(glm::vec3(pointCenter + glm::vec3(0, -solutionPointRadius, 0)), 0.5f, 0.5f);
                RenderVertex cornerZp = RenderVertex(glm::vec3(pointCenter + glm::vec3(0, 0, solutionPointRadius)), 0.5f, 0.5f);
                RenderVertex cornerZm = RenderVertex(glm::vec3(pointCenter + glm::vec3(0, 0, -solutionPointRadius)), 0.5f, 0.5f);
                //Create triangles
                solutionTriangles.emplace_back(RenderTriangle(TextureType::WHITE, cornerXp, cornerYp, cornerZp));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::WHITE, cornerZp, cornerYp, cornerXm));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::WHITE, cornerZp, cornerYm, cornerXp));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::WHITE, cornerXm, cornerYm, cornerZp));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::WHITE, cornerZm, cornerYp, cornerXp));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::WHITE, cornerXm, cornerYp, cornerZm));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::WHITE, cornerXp, cornerYm, cornerZm));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::WHITE, cornerZm, cornerYm, cornerXm));
            }
        }
    }

    return solutionTriangles;
}

//private:
std::list<RenderTriangle> Solver::markAndCreateCubes(bool *** cubeMatrix, SolverPoint *** grid,
        const std::list<RenderTriangle> & trianglesToCube, TextureType textureID, bool isSource) const {
    //--- CREATE CUBES ---//
    std::list<RenderTriangle> cubeRenderTriangles;
    for (const RenderTriangle & renT : trianglesToCube) {
        //Get triangle points
        glm::vec3 point1;
        glm::vec3 point2;
        glm::vec3 point3;
        std::list<RenderVertex>::const_iterator actVertex = renT.getVertices().begin();
        for (int i = 0; i < renT.getVertices().size(); i++) {
            switch (i) {
                case 0: {
                    point1 = glm::vec3(actVertex->getX(), actVertex->getY(), actVertex->getZ());
                    break;
                }
                case 1: {
                    point2 = glm::vec3(actVertex->getX(), actVertex->getY(), actVertex->getZ());
                    break;
                }
                case 2: {
                    point3 = glm::vec3(actVertex->getX(), actVertex->getY(), actVertex->getZ());
                    break;
                }
                default: {
                    std::cout << "Error: Triangle should not have more than 3 vertices!" << std::endl;
                    break;
                }
            }
            actVertex++;
        }
        //Calculate normal vector
        glm::vec3 vec1 = point2 - point1;
        glm::vec3 vec2 = point3 - point1;
        glm::vec3 normalVector = glm::normalize(glm::cross(vec1, vec2));
        //Find corner cubes
        glm::ivec3 corner1 = glm::ivec3(int((point1.x - _minX)/_edgeLength),
                                        int((point1.y - _minY)/_edgeLength),
                                        int((point1.z - _minZ)/_edgeLength));
        glm::ivec3 corner2 = glm::ivec3(int((point2.x - _minX)/_edgeLength),
                                        int((point2.y - _minY)/_edgeLength),
                                        int((point2.z - _minZ)/_edgeLength));
        glm::ivec3 corner3 = glm::ivec3(int((point3.x - _minX)/_edgeLength),
                                        int((point3.y - _minY)/_edgeLength),
                                        int((point3.z - _minZ)/_edgeLength));
        //Find cubes on edges
        std::list<glm::ivec3> edge1Cubes = findCubesOnLine(corner1, corner2);
        std::list<glm::ivec3> edge2Cubes = findCubesOnLine(corner2, corner3);
        std::list<glm::ivec3> edge3Cubes = findCubesOnLine(corner1, corner3);
        //Mark cubes on on triangle
        for (const glm::ivec3 & startEdgeCube : edge1Cubes) {
            for (const glm::ivec3 & endEdgeCube : edge2Cubes) {
                std::list<glm::ivec3> cubes = findCubesOnLine(startEdgeCube, endEdgeCube);
                for (const glm::ivec3 & cube : cubes) {
                    cubeMatrix[cube.x][cube.y][cube.z] = true;
                }
            }
        }
        for (const glm::ivec3 & startEdgeCube : edge1Cubes) {
            for (const glm::ivec3 & endEdgeCube : edge3Cubes) {
                std::list<glm::ivec3> cubes = findCubesOnLine(startEdgeCube, endEdgeCube);
                for (const glm::ivec3 & cube : cubes) {
                    cubeMatrix[cube.x][cube.y][cube.z] = true;
                }
            }
        }
        for (const glm::ivec3 & startEdgeCube : edge2Cubes) {
            for (const glm::ivec3 & endEdgeCube : edge3Cubes) {
                std::list<glm::ivec3> cubes = findCubesOnLine(startEdgeCube, endEdgeCube);
                for (const glm::ivec3 & cube : cubes) {
                    cubeMatrix[cube.x][cube.y][cube.z] = true;
                }
            }
        }

        //Create render triangles from cube matrix
        for (int k = 0; k < _pointMatrixSizeZ; k++) {
            for (int j = 0; j < _pointMatrixSizeY; j++) {
                for (int i = 0; i < _pointMatrixSizeX; i++) {
                    if (cubeMatrix[i][j][k]) {
                        //Create points
                        RenderVertex pointNNN = RenderVertex(_minX + i*_edgeLength, _minY + j*_edgeLength, _minZ + k*_edgeLength, 0.f, 0.f);
                        RenderVertex pointNNP = RenderVertex(_minX + i*_edgeLength, _minY + j*_edgeLength, _minZ + (k+1)*_edgeLength, 0.f, 0.f);
                        RenderVertex pointNPN = RenderVertex(_minX + i*_edgeLength, _minY + (j+1)*_edgeLength, _minZ + k*_edgeLength, 0.f, 0.f);
                        RenderVertex pointNPP = RenderVertex(_minX + i*_edgeLength, _minY + (j+1)*_edgeLength, _minZ + (k+1)*_edgeLength, 0.f, 0.f);
                        RenderVertex pointPNN = RenderVertex(_minX + (i+1)*_edgeLength, _minY + j*_edgeLength, _minZ + k*_edgeLength, 0.f, 0.f);
                        RenderVertex pointPNP = RenderVertex(_minX + (i+1)*_edgeLength, _minY + j*_edgeLength, _minZ + (k+1)*_edgeLength, 0.f, 0.f);
                        RenderVertex pointPPN = RenderVertex(_minX + (i+1)*_edgeLength, _minY + (j+1)*_edgeLength, _minZ + k*_edgeLength, 0.f, 0.f);
                        RenderVertex pointPPP = RenderVertex(_minX + (i+1)*_edgeLength, _minY + (j+1)*_edgeLength, _minZ + (k+1)*_edgeLength, 0.f, 0.f);
                        //Create +X plane
                        pointPNP.setTexPosition(0.f, 0.f);
                        pointPPP.setTexPosition(1.f, 0.f);
                        pointPPN.setTexPosition(1.f, 1.f);
                        pointPNN.setTexPosition(0.f, 1.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPNN, pointPPN, pointPPP));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPPP, pointPNP, pointPNN));
                        //Create -X plane
                        pointNPP.setTexPosition(0.f, 0.f);
                        pointNPN.setTexPosition(0.f, 1.f);
                        pointNNN.setTexPosition(1.f, 1.f);
                        pointNNP.setTexPosition(1.f, 0.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNPP, pointNPN, pointNNN));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNNN, pointNNP, pointNPP));
                        //Create +Y plane
                        pointNPP.setTexPosition(1.f, 0.f);
                        pointPPP.setTexPosition(0.f, 0.f);
                        pointPPN.setTexPosition(0.f, 1.f);
                        pointNPN.setTexPosition(1.f, 1.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNPP, pointPPP, pointPPN));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPPN, pointNPN, pointNPP));
                        //Create -Y plane
                        pointNNP.setTexPosition(0.f, 0.f);
                        pointPNP.setTexPosition(1.f, 0.f);
                        pointPNN.setTexPosition(1.f, 1.f);
                        pointNNN.setTexPosition(0.f, 1.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNNP, pointNNN, pointPNN));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPNN, pointPNP, pointNNP));
                        //Create +Z plane
                        pointNPP.setTexPosition(1.f, 1.f);
                        pointPPP.setTexPosition(0.f, 1.f);
                        pointPNP.setTexPosition(0.f, 0.f);
                        pointNNP.setTexPosition(1.f, 0.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNPP, pointNNP, pointPNP));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPNP, pointPPP, pointNPP));
                        //Create -Z plane
                        pointNPN.setTexPosition(0.f, 0.f);
                        pointPPN.setTexPosition(1.f, 0.f);
                        pointPNN.setTexPosition(1.f, 1.f);
                        pointNNN.setTexPosition(0.f, 1.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNPN, pointPPN, pointPNN));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPNN, pointNNN, pointNPN));
                    }
                }
            }
        }

        if (!isSource) {
            //--- SET NORMAL VECTORS ---//
            for (int k = 0; k < _pointMatrixSizeZ; k++) {
                for (int j = 0; j < _pointMatrixSizeY; j++) {
                    for (int i = 0; i < _pointMatrixSizeX; i++) {
                        if (cubeMatrix[i][j][k]) {
                            if (glm::dot(normalVector, glm::vec3(-_edgeLength/2, -_edgeLength/2, -_edgeLength/2)) > 0) {
                                grid[i][j][k].setNormalVector(grid[i][j][k].getNormalVector() + normalVector);
                            } else {
                                grid[i][j][k].setNormalVector(grid[i][j][k].getNormalVector() - normalVector);
                            }

                            if (glm::dot(normalVector, glm::vec3(_edgeLength/2, -_edgeLength/2, -_edgeLength/2)) > 0) {
                                grid[i + 1][j][k].setNormalVector(grid[i + 1][j][k].getNormalVector() + normalVector);
                            } else {
                                grid[i + 1][j][k].setNormalVector(grid[i + 1][j][k].getNormalVector() - normalVector);
                            }

                            if (glm::dot(normalVector, glm::vec3(-_edgeLength/2, _edgeLength/2, -_edgeLength/2)) > 0) {
                                grid[i][j + 1][k].setNormalVector(grid[i][j + 1][k].getNormalVector() + normalVector);
                            } else {
                                grid[i][j + 1][k].setNormalVector(grid[i][j + 1][k].getNormalVector() - normalVector);
                            }

                            if (glm::dot(normalVector, glm::vec3(-_edgeLength/2, -_edgeLength/2, _edgeLength/2)) > 0) {
                                grid[i][j][k + 1].setNormalVector(grid[i][j][k + 1].getNormalVector() + normalVector);
                            } else {
                                grid[i][j][k + 1].setNormalVector(grid[i][j][k + 1].getNormalVector() - normalVector);
                            }

                            if (glm::dot(normalVector, glm::vec3(_edgeLength/2, _edgeLength/2, -_edgeLength/2)) > 0) {
                                grid[i + 1][j + 1][k].setNormalVector(grid[i + 1][j + 1][k].getNormalVector() + normalVector);
                            } else {
                                grid[i + 1][j + 1][k].setNormalVector(grid[i + 1][j + 1][k].getNormalVector() - normalVector);
                            }

                            if (glm::dot(normalVector, glm::vec3(_edgeLength/2, -_edgeLength/2, _edgeLength/2)) > 0) {
                                grid[i + 1][j][k + 1].setNormalVector(grid[i + 1][j][k + 1].getNormalVector() + normalVector);
                            } else {
                                grid[i + 1][j][k + 1].setNormalVector(grid[i + 1][j][k + 1].getNormalVector() - normalVector);
                            }

                            if (glm::dot(normalVector, glm::vec3(-_edgeLength/2, _edgeLength/2, _edgeLength/2)) > 0) {
                                grid[i][j + 1][k + 1].setNormalVector(grid[i][j + 1][k + 1].getNormalVector() + normalVector);
                            } else {
                                grid[i][j + 1][k + 1].setNormalVector(grid[i][j + 1][k + 1].getNormalVector() - normalVector);
                            }

                            if (glm::dot(normalVector, glm::vec3(_edgeLength/2, _edgeLength/2, _edgeLength/2)) > 0) {
                                grid[i + 1][j + 1][k + 1].setNormalVector(grid[i + 1][j + 1][k + 1].getNormalVector() + normalVector);
                            } else {
                                grid[i + 1][j + 1][k + 1].setNormalVector(grid[i + 1][j + 1][k + 1].getNormalVector() - normalVector);
                            }
                        }
                    }
                }
            }
        } else {
            //--- SET SOURCES ---//
            for (int k = 0; k < _pointMatrixSizeZ; k++) {
                for (int j = 0; j < _pointMatrixSizeY; j++) {
                    for (int i = 0; i < _pointMatrixSizeX; i++) {
                        if (cubeMatrix[i][j][k]) {
                            grid[i][j][k].setToSource(ComplexFloat(1.f, 0.f));
                            grid[i+1][j][k].setToSource(ComplexFloat(1.f, 0.f));
                            grid[i][j+1][k].setToSource(ComplexFloat(1.f, 0.f));
                            grid[i+1][j+1][k].setToSource(ComplexFloat(1.f, 0.f));
                            grid[i][j][k+1].setToSource(ComplexFloat(1.f, 0.f));
                            grid[i+1][j][k+1].setToSource(ComplexFloat(1.f, 0.f));
                            grid[i][j+1][k+1].setToSource(ComplexFloat(1.f, 0.f));
                            grid[i+1][j+1][k+1].setToSource(ComplexFloat(1.f, 0.f));
                        }
                    }
                }
            }
        }

        //Clear cube matrix
        for (int k = 0; k < _pointMatrixSizeZ; k++) {
            for (int j = 0; j < _pointMatrixSizeY; j++) {
                for (int i = 0; i < _pointMatrixSizeX; i++) {
                    cubeMatrix[i][j][k] = false;
                }
            }
        }
    }

    if (!isSource) {
        //Normalize normal vectors
        for (int k = 0; k < _pointMatrixSizeZ + 1; k++) {
            for (int j = 0; j < _pointMatrixSizeY + 1; j++) {
                for (int i = 0; i < _pointMatrixSizeX + 1; i++) {
                    if (grid[i][j][k].getNormalVector() != glm::vec3(0, 0, 0)) {
                        grid[i][j][k].setNormalVector(glm::normalize(grid[i][j][k].getNormalVector()));
                    }
                }
            }
        }
        //Create normals render triangles
        std::list<RenderTriangle> normalsRenderTriangles;
        for (int k = 0; k < _pointMatrixSizeZ + 1; k++) {
            for (int j = 0; j < _pointMatrixSizeY + 1; j++) {
                for (int i = 0; i < _pointMatrixSizeX + 1; i++) {
                    if (grid[i][j][k].getNormalVector() != glm::vec3(0, 0, 0)) {
                        glm::vec3 pointPosition = glm::vec3(_minX + i * _edgeLength, _minY + j * _edgeLength,
                                                            _minZ + k * _edgeLength);
                        glm::vec3 firstSideVector;
                        glm::vec3 secondSideVector;
                        if (abs(grid[i][j][k].getNormalVector().x) > abs(grid[i][j][k].getNormalVector().z)) {
                            firstSideVector = glm::normalize(
                                    glm::cross(grid[i][j][k].getNormalVector(), glm::vec3(0, 0, 1)));
                        } else {
                            firstSideVector = glm::normalize(
                                    glm::cross(grid[i][j][k].getNormalVector(), glm::vec3(1, 0, 0)));
                        }
                        secondSideVector = glm::normalize(glm::cross(grid[i][j][k].getNormalVector(), firstSideVector));

                        glm::vec3 point0Position = pointPosition + 0.03f * grid[i][j][k].getNormalVector();
                        glm::vec3 point11Position = pointPosition + 0.007f * firstSideVector;
                        glm::vec3 point12Position = pointPosition - 0.007f * firstSideVector;
                        glm::vec3 point21Position = pointPosition + 0.007f * secondSideVector;
                        glm::vec3 point22Position = pointPosition - 0.007f * secondSideVector;

                        normalsRenderTriangles.emplace_back(
                                RenderTriangle(textureID, RenderVertex(point11Position, 0, 0),
                                               RenderVertex(point0Position, 1, 0),
                                               RenderVertex(point12Position, 1, 1)));
                        normalsRenderTriangles.emplace_back(
                                RenderTriangle(textureID, RenderVertex(point12Position, 0, 0),
                                               RenderVertex(point0Position, 1, 0),
                                               RenderVertex(point11Position, 1, 1)));
                        normalsRenderTriangles.emplace_back(
                                RenderTriangle(textureID, RenderVertex(point21Position, 0, 0),
                                               RenderVertex(point0Position, 1, 0),
                                               RenderVertex(point22Position, 1, 1)));
                        normalsRenderTriangles.emplace_back(
                                RenderTriangle(textureID, RenderVertex(point22Position, 0, 0),
                                               RenderVertex(point0Position, 1, 0),
                                               RenderVertex(point21Position, 1, 1)));
                    }
                }
            }
        }
        return normalsRenderTriangles;
    } else {
        return cubeRenderTriangles;
    }


//    //Print cubes
//    for (int k = 0; k < _pointMatrixSizeZ; k++) {
//        for (int j = 0; j < _pointMatrixSizeY; j++) {
//            for (int i = 0; i < _pointMatrixSizeX; i++) {
//                std::cout << cubeMatrix[i][j][k] << '\t';
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//    }

}

std::list<glm::ivec3> Solver::findCubesOnLine(const glm::ivec3 & point1, const glm::ivec3 & point2) const {
    std::list<glm::ivec3> cubes;
    glm::vec3 targetVector = point2 - point1;
    glm::vec3 actVector = glm::vec3(0.f,0.f,0.f);
    cubes.emplace_back(glm::ivec3(int(std::round(actVector.x + point1.x)),
            int(std::round(actVector.y + point1.y)),
            int(std::round(actVector.z + point1.z))));
    float distances[7]; // 0 - no change,
                        // 1 - X+1,
                        // 2 - Y+1,
                        // 3 - Z+1,
                        // 4 - X-1,
                        // 5 - Y-1,
                        // 6 - Z-1
    int minArg;
    while(glm::distance(actVector, targetVector) > 0.5f) {
        //Prepare all possible direction vectors
        glm::vec3 vectors[7];
        vectors[0] = actVector;
        vectors[1] = glm::vec3(actVector.x + 1, actVector.y, actVector.z);
        vectors[2] = glm::vec3(actVector.x, actVector.y + 1, actVector.z);
        vectors[3] = glm::vec3(actVector.x, actVector.y, actVector.z + 1);
        vectors[4] = glm::vec3(actVector.x - 1, actVector.y, actVector.z);
        vectors[5] = glm::vec3(actVector.x, actVector.y - 1, actVector.z);
        vectors[6] = glm::vec3(actVector.x, actVector.y, actVector.z - 1);
        //Get max possible length
        for (int i = 0; i < 7; i++) {
            distances[i] = glm::length(vectors[i]);
        }
        int maxLengthArg = 1;
        for (int i = 2; i < 7; i++) {
            if (distances[i] > distances[maxLengthArg]) {
                maxLengthArg = i;
            }
        }
        float maxLength = distances[maxLengthArg];
        //Prepare direction vector distances
        glm::vec3 actTargetVector = glm::normalize(targetVector) * maxLength;
        for (int i = 0; i < 7; i++) {
            distances[i] = glm::distance(vectors[i], actTargetVector);
        }
        //Find minimum distance
        minArg = 1;
        for (int i = 2; i < 7; i++) {
            if (distances[i] < distances[minArg]) {
                minArg = i;
            }
        }
        //Add to list
        actVector = vectors[minArg];
        cubes.emplace_back(glm::ivec3(int(std::round(actVector.x + point1.x)),
                int(std::round(actVector.y + point1.y)),
                int(std::round(actVector.z + point1.z))));
    }
    return cubes;
}

MatrixSystemOfEquations Solver::createSystemOfEquations(SolverPoint *** grid) const {
    //Reserve memory
    int numberOfVariables = (_pointMatrixSizeX+1)*(_pointMatrixSizeY+1)*(_pointMatrixSizeZ+1);
    std::cout << "Number of variables: " << numberOfVariables << std::endl;
    MatrixSystemOfEquations systemOfEquations(numberOfVariables);

    //Fill equations
    for (int i = 0; i < _pointMatrixSizeX+1; i++) {
        for (int j = 0; j < _pointMatrixSizeY+1; j++) {
            for (int k = 0; k < _pointMatrixSizeZ+1; k++) {
                int actID = calculateVariableIndex(i,j,k);
                if (grid[i][j][k].isSource()) {
                    //Source
                    const ComplexFloat & pressure = grid[i][j][k].getPressure();

                    systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f));
                    systemOfEquations.setConstant(actID, pressure);

                } else {
                    //Check borders
                    bool xp = false;
                    bool xm = false;
                    bool yp = false;
                    bool ym = false;
                    bool zp = false;
                    bool zm = false;
                    if (i == 0) {
                        xm = true;
                    } else if (i == _pointMatrixSizeX) {
                        xp = true;
                    }
                    if (j == 0) {
                        ym = true;
                    } else if (j == _pointMatrixSizeY) {
                        yp = true;
                    }
                    if (k == 0) {
                        zm = true;
                    } else if (k == _pointMatrixSizeZ) {
                        zp = true;
                    }
                    //Pre-calculate constants
                    float wallDerivativeFactor = _SOUND_SPEED/_angularFrequency/_edgeLength;
                    float edgeDerivativeFactor = wallDerivativeFactor/sqrt(2.f);
                    float cornerDerivativeFactor = wallDerivativeFactor/sqrt(3.f);
                    //Borders
                    if (xm) {
                        if (ym) {
                            if (zm) {
                                //Corner XmYmZm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*cornerDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j+1,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*cornerDerivativeFactor);
                            } else if (zp) {
                                //Corner XmYmZp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*cornerDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j+1,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*cornerDerivativeFactor);
                            } else {
                                //Edge XmYm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j+1,k), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            }
                        } else if (yp) {
                            if (zm) {
                                //Corner XmYpZm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*cornerDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j-1,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*cornerDerivativeFactor);
                            } else if (zp) {
                                //Corner XmYpZp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*cornerDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j-1,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*cornerDerivativeFactor);
                            } else {
                                //Edge XmYp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j-1,k), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            }
                        } else {
                            if (zm) {
                                //Edge XmZm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            } else if (zp) {
                                //Edge XmZp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            } else {
                                //Wall Xm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*wallDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k), actID, ComplexFloat(0.f, 1.f)*(-1)*wallDerivativeFactor);
                            }
                        }
                    } else if (xp) {
                        if (ym) {
                            if (zm) {
                                //Corner XpYmZm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*cornerDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j+1,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*cornerDerivativeFactor);
                            } else if (zp) {
                                //Corner XpYmZp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*cornerDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j+1,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*cornerDerivativeFactor);
                            } else {
                                //Edge XpYm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j+1,k), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            }
                        } else if (yp) {
                            if (zm) {
                                //Corner XpYpZm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*cornerDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j-1,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*cornerDerivativeFactor);
                            } else if (zp) {
                                //Corner XpYpZp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*cornerDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j-1,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*cornerDerivativeFactor);
                            } else {
                                //Edge XpYp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j-1,k), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            }
                        } else {
                            if (zm) {
                                //Edge XpZm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            } else if (zp) {
                                //Edge XpZp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            } else {
                                //Wall Xp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*wallDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k), actID, ComplexFloat(0.f, 1.f)*(-1)*wallDerivativeFactor);
                            }
                        }
                    } else {
                        if (ym) {
                            if (zm) {
                                //Edge YmZm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            } else if (zp) {
                                //Edge YmZp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            } else {
                                //Wall Ym
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*wallDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k), actID, ComplexFloat(0.f, 1.f)*(-1)*wallDerivativeFactor);
                            }
                        } else if (yp) {
                            if (zm) {
                                //Edge YpZm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            } else if (zp) {
                                //Edge YpZp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*edgeDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*edgeDerivativeFactor);
                            } else {
                                //Wall Yp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*wallDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k), actID, ComplexFloat(0.f, 1.f)*(-1)*wallDerivativeFactor);
                            }
                        } else {
                            if (zm) {
                                //Wall Zm
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*wallDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1), actID, ComplexFloat(0.f, 1.f)*(-1)*wallDerivativeFactor);
                            } else if (zp) {
                                //Wall Zp
                                systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f) + ComplexFloat(0.f, 1.f)*wallDerivativeFactor);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1), actID, ComplexFloat(0.f, 1.f)*(-1)*wallDerivativeFactor);
                            } else {
//                                //Not a border
//                                glm::vec3 direction = grid[i][j][k].getNormalVector();
//                                if (direction != glm::vec3(0,0,0)) {
//                                    //Reflection
//                                    //Scale normal vector
//                                    direction *= _edgeLength;
//                                    //Calculate distances from walls
//                                    float distXs = direction.x;
//                                    float distYs = direction.y;
//                                    float distZs = direction.z;
//                                    float distXo = _edgeLength - direction.x;
//                                    float distYo = _edgeLength - direction.y;
//                                    float distZo = _edgeLength - direction.z;
//                                    //Calculate distances from corners
//                                    float distXsYsZs = max(abs(distXs), abs(distYs), abs(distZs));
//                                    float distXoYsZs = max(abs(distXo), abs(distYs), abs(distZs));
//                                    float distXsYoZs = max(abs(distXs), abs(distYo), abs(distZs));
//                                    float distXoYoZs = max(abs(distXo), abs(distYo), abs(distZs));
//                                    float distXsYsZo = max(abs(distXs), abs(distYs), abs(distZo));
//                                    float distXoYsZo = max(abs(distXo), abs(distYs), abs(distZo));
//                                    float distXsYoZo = max(abs(distXs), abs(distYo), abs(distZo));
//                                    float distXoYoZo = max(abs(distXo), abs(distYo), abs(distZo));
//                                    //Calculate point factors
//                                    float factXsYsZs = 1 - distXsYsZs;
//                                    float factXoYsZs = 1 - distXoYsZs;
//                                    float factXsYoZs = 1 - distXsYoZs;
//                                    float factXoYoZs = 1 - distXoYoZs;
//                                    float factXsYsZo = 1 - distXsYsZo;
//                                    float factXoYsZo = 1 - distXoYsZo;
//                                    float factXsYoZo = 1 - distXsYoZo;
//                                    float factXoYoZo = 1 - distXoYoZo;
//                                    float denominator = 2*_edgeLength*(factXsYsZs+factXoYsZs+factXsYoZs+factXoYoZs+
//                                            factXsYsZo+factXoYsZo+factXsYoZo+factXoYoZo);
//                                    //Set variable factors
//                                    systemOfEquations.set(actID, actID, ComplexFloat(1.f, 0.f)*factXsYsZs/denominator - ComplexFloat(1.f, 0.f));
//                                    systemOfEquations.set(calculateVariableIndex(i+pseudoSignum(distXs),j,k), actID, ComplexFloat(1.f, 0.f)*factXoYsZs/denominator);
////                                    systemOfEquations.set(calculateVariableIndex(i-pseudoSignum(distXs),j,k), actID, ComplexFloat(1.f, 0.f)*-factXoYsZs/denominator);
//                                    systemOfEquations.set(calculateVariableIndex(i,j+pseudoSignum(distYs),k), actID, ComplexFloat(1.f, 0.f)*factXsYoZs/denominator);
////                                    systemOfEquations.set(calculateVariableIndex(i,j-pseudoSignum(distYs),k), actID, ComplexFloat(1.f, 0.f)*-factXsYoZs/denominator);
//                                    systemOfEquations.set(calculateVariableIndex(i,j,k+pseudoSignum(distZs)), actID, ComplexFloat(1.f, 0.f)*factXsYsZo/denominator);
////                                    systemOfEquations.set(calculateVariableIndex(i,j,k-pseudoSignum(distZs)), actID, ComplexFloat(1.f, 0.f)*-factXsYsZo/denominator);
//                                    systemOfEquations.set(calculateVariableIndex(i+pseudoSignum(distXs),j+pseudoSignum(distYs),k), actID, ComplexFloat(1.f, 0.f)*factXoYoZs/denominator);
////                                    systemOfEquations.set(calculateVariableIndex(i-pseudoSignum(distXs),j-pseudoSignum(distYs),k), actID, ComplexFloat(1.f, 0.f)*-factXoYoZs/denominator);
//                                    systemOfEquations.set(calculateVariableIndex(i+pseudoSignum(distXs),j,k+pseudoSignum(distZs)), actID, ComplexFloat(1.f, 0.f)*factXoYsZo/denominator);
////                                    systemOfEquations.set(calculateVariableIndex(i-pseudoSignum(distXs),j,k-pseudoSignum(distZs)), actID, ComplexFloat(1.f, 0.f)*-factXoYsZo/denominator);
//                                    systemOfEquations.set(calculateVariableIndex(i,j+pseudoSignum(distYs),k+pseudoSignum(distZs)), actID, ComplexFloat(1.f, 0.f)*factXsYoZo/denominator);
////                                    systemOfEquations.set(calculateVariableIndex(i,j-pseudoSignum(distYs),k-pseudoSignum(distZs)), actID, ComplexFloat(1.f, 0.f)*-factXsYoZo/denominator);
//                                    systemOfEquations.set(calculateVariableIndex(i+pseudoSignum(distXs),j+pseudoSignum(distYs),k+pseudoSignum(distZs)), actID, ComplexFloat(1.f, 0.f)*factXoYoZo/denominator);
////                                    systemOfEquations.set(calculateVariableIndex(i-pseudoSignum(distXs),j-pseudoSignum(distYs),k-pseudoSignum(distZs)), actID, ComplexFloat(1.f, 0.f)*-factXoYoZo/denominator);
//
//                                } else {
                                    //Helmholtz equation
                                    systemOfEquations.set(calculateVariableIndex(i+1,j,k), actID, ComplexFloat(1.f, 0.f));
                                    systemOfEquations.set(calculateVariableIndex(i-1,j,k), actID, ComplexFloat(1.f, 0.f));
                                    systemOfEquations.set(calculateVariableIndex(i,j+1,k), actID, ComplexFloat(1.f, 0.f));
                                    systemOfEquations.set(calculateVariableIndex(i,j-1,k), actID, ComplexFloat(1.f, 0.f));
                                    systemOfEquations.set(calculateVariableIndex(i,j,k+1), actID, ComplexFloat(1.f, 0.f));
                                    systemOfEquations.set(calculateVariableIndex(i,j,k-1), actID, ComplexFloat(1.f, 0.f));
                                    systemOfEquations.set(actID, actID, ComplexFloat(_edgeLength*_edgeLength*_waveLength*_waveLength - 6, 0.f));
//                                }
                            }
                        }
                    }
                }
//                systemOfEquations.print(actID);
            }
        }
    }

    return systemOfEquations;
}

int Solver::calculateVariableIndex(int i, int j, int k) const {
    return (_pointMatrixSizeX + 1)*((_pointMatrixSizeY + 1)*k + j) + i;
}

int Solver::pseudoSignum(float x) const {
    if (x >= 0.f) {
        return 1;
    } else {
        return -1;
    }
}

float Solver::max(float x, float y, float z) const {
    if (x >= y) {
        if (x >= z) {
            return x;
        }
    } else {
        if (y >= z) {
            return y;
        }
    }
    return z;
}
