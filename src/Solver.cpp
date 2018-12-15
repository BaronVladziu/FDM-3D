//
// Created by baronvladziu on 08.09.18.
//

#include "Solver.h"
#include "JacobiSystemOfEquations.h"


constexpr float Solver::_THIRD_OCTAVE_BANDS[];
constexpr float Solver::_OCTAVE_BANDS[];

//public:
std::unique_ptr<std::list<RenderTriangle>> Solver::solveRoom(const Map & map, const SolverConfiguration & config) {

    std::cout << "\n--- SOLVING ROOM FOR VISUALIZATION ---" << std::endl;
    createGrid(map, config.MAIN_FREQUENCY, config.MINIMAL_NUMBER_OF_POINTS_PER_PERIOD);

    //Prepare triangles
    const std::list<RenderTriangle> & wallTriangles = map.getWallTriangles();
    const std::list<RenderTriangle> & speakerTriangles = map.getSpeakerTriangles();

    //--- SET WALLS---//
    std::unique_ptr<std::list<RenderTriangle>> cubeTriangles = markAndCreateCubes(_cubeMatrix, _grid, wallTriangles, TextureType::WALL, false);
    std::unique_ptr<std::list<RenderTriangle>> cubesSpeakerTriangles = markAndCreateCubes(_cubeMatrix, _grid, speakerTriangles, TextureType::SPEAKER, true);
    cubeTriangles->insert(cubeTriangles->end(), cubesSpeakerTriangles->begin(), cubesSpeakerTriangles->end());

    //Print equations
//    std::cout << "Saving results:" << std::endl;
//    std::ofstream myfile;
//    myfile.open ("equations.txt");
//    for (int j = 0; j < equations.getNumberOfVariables(); j++) {
//        for (int i = 0; i < equations.getNumberOfVariables(); i++) {
//            myfile << equations.get(i, j).real << "+" << equations.get(i, j).imag << "i\t";
//        }
//        myfile << equations.getConstant(j).real << "+" << equations.getConstant(j).imag << "i\t";
//        myfile << std::endl;
//    }
//    myfile << std::endl;
//    myfile.close();

    //--- SOLVE EQUATIONS ---//
    JacobiSystemOfEquations equations = createSystemOfEquations(_grid);
    equations.solve();

    deleteGrid();

    return createSolutionTriangles(equations, config, wallTriangles, speakerTriangles);
}
std::unique_ptr<std::list<RenderTriangle>> Solver::solveReceivers(const Map & map, const SolverConfiguration & config) {
    std::list<std::pair<float, ComplexFloat>> * results = new std::list<std::pair<float, ComplexFloat>>[map.getReceivers().size()];
    std::unique_ptr<std::list<RenderTriangle>> solutionTriangles;
    bool areSolutionTrianglesSaved = false;
    for (int bandID = _NUMBER_OF_THIRD_OCTAVE_BANDS - 1; bandID >= 0; bandID--) {
        float freqBand = _THIRD_OCTAVE_BANDS[bandID];
        if (freqBand >= config.START_FREQUENCY && freqBand <= config.STOP_FREQUENCY) {
            std::cout << "\n--- SOLVING FOR " << freqBand << " Hz ---" << std::endl;
            createGrid(map, freqBand, config.MINIMAL_NUMBER_OF_POINTS_PER_PERIOD);

            //Prepare triangles
            const std::list<RenderTriangle> & wallTriangles = map.getWallTriangles();
            const std::list<RenderTriangle> & speakerTriangles = map.getSpeakerTriangles();

            //--- SET WALLS---//
            std::unique_ptr<std::list<RenderTriangle>> cubeTriangles = markAndCreateCubes(_cubeMatrix, _grid, wallTriangles, TextureType::WALL, false);
            std::unique_ptr<std::list<RenderTriangle>> cubesSpeakerTriangles = markAndCreateCubes(_cubeMatrix, _grid, speakerTriangles, TextureType::SPEAKER, true);
            cubeTriangles->insert(cubeTriangles->end(), cubesSpeakerTriangles->begin(), cubesSpeakerTriangles->end());

            //--- SOLVE EQUATIONS ---//
            JacobiSystemOfEquations equations = createSystemOfEquations(_grid);
            equations.solve();

            deleteGrid();

            //--- SAVE RECEIVER SOLUTIONS ---//
            std::cout << "Saving receiver results:" << std::endl;
            int receiverID = 0;
            for (const RenderVertex & receiver : map.getReceivers()) {
                //Find surrounding points
                int floorX = int((receiver.getX() - _minX)/_edgeLength);
                float distX = receiver.getX() - (_minX + floorX*_edgeLength);
                assert(distX >= 0.f);
                assert(distX <= _edgeLength);
                int floorY = int((receiver.getY() - _minY)/_edgeLength);
                float distY = receiver.getY() - (_minY + floorY*_edgeLength);
                assert(distX >= 0.f);
                assert(distX <= _edgeLength);
                int floorZ = int((receiver.getZ() - _minZ)/_edgeLength);
                float distZ = receiver.getZ() - (_minZ + floorZ*_edgeLength);
                assert(distX >= 0.f);
                assert(distX <= _edgeLength);
                //Calculate value
                float realNumerator = 0.f;
                float imagNumerator = 0.f;
                float denominator = 0.f;
                //---
                float wage = _edgeLength - max(distX, distY, distZ);
                assert(wage >= 0.f);
                realNumerator += equations.getSolution(calculateVariableIndex(floorX, floorY, floorZ, false))*wage;
                imagNumerator += equations.getSolution(calculateVariableIndex(floorX, floorY, floorZ, true))*wage;
                denominator += wage;
                //+--
                wage = _edgeLength - max(_edgeLength - distX, distY, distZ);
                assert(wage >= 0.f);
                realNumerator += equations.getSolution(calculateVariableIndex(floorX+1, floorY, floorZ, false))*wage;
                imagNumerator += equations.getSolution(calculateVariableIndex(floorX+1, floorY, floorZ, true))*wage;
                denominator += wage;
                //-+-
                wage = _edgeLength - max(distX, _edgeLength - distY, distZ);
                assert(wage >= 0.f);
                realNumerator += equations.getSolution(calculateVariableIndex(floorX, floorY+1, floorZ, false))*wage;
                imagNumerator += equations.getSolution(calculateVariableIndex(floorX, floorY+1, floorZ, true))*wage;
                denominator += wage;
                //++-
                wage = _edgeLength - max(_edgeLength - distX, _edgeLength - distY, distZ);
                assert(wage >= 0.f);
                realNumerator += equations.getSolution(calculateVariableIndex(floorX+1, floorY+1, floorZ, false))*wage;
                imagNumerator += equations.getSolution(calculateVariableIndex(floorX+1, floorY+1, floorZ, true))*wage;
                denominator += wage;
                //--+
                wage = _edgeLength - max(distX, distY, _edgeLength - distZ);
                assert(wage >= 0.f);
                realNumerator += equations.getSolution(calculateVariableIndex(floorX, floorY, floorZ+1, false))*wage;
                imagNumerator += equations.getSolution(calculateVariableIndex(floorX, floorY, floorZ+1, true))*wage;
                denominator += wage;
                //+-+
                wage = _edgeLength - max(_edgeLength - distX, distY, _edgeLength - distZ);
                assert(wage >= 0.f);
                realNumerator += equations.getSolution(calculateVariableIndex(floorX+1, floorY, floorZ+1, false))*wage;
                imagNumerator += equations.getSolution(calculateVariableIndex(floorX+1, floorY, floorZ+1, true))*wage;
                denominator += wage;
                //-++
                wage = _edgeLength - max(distX, _edgeLength - distY, _edgeLength - distZ);
                assert(wage >= 0.f);
                realNumerator += equations.getSolution(calculateVariableIndex(floorX, floorY+1, floorZ+1, false))*wage;
                imagNumerator += equations.getSolution(calculateVariableIndex(floorX, floorY+1, floorZ+1, true))*wage;
                denominator += wage;
                //+++
                wage = _edgeLength - max(_edgeLength - distX, _edgeLength - distY, _edgeLength - distZ);
                assert(wage >= 0.f);
                realNumerator += equations.getSolution(calculateVariableIndex(floorX+1, floorY+1, floorZ+1, false))*wage;
                imagNumerator += equations.getSolution(calculateVariableIndex(floorX+1, floorY+1, floorZ+1, true))*wage;
                denominator += wage;
                //Save
                results[receiverID].emplace_back(std::pair<float, ComplexFloat>(freqBand, ComplexFloat(realNumerator/denominator, imagNumerator/denominator)));
                receiverID++;
            }

            if (!areSolutionTrianglesSaved) {
                solutionTriangles = createSolutionTriangles(equations, config, wallTriangles, speakerTriangles);
                areSolutionTrianglesSaved = true;
            }
        }
    }

    //Save to file
    std::ofstream myfile;
    myfile.open("receiver-results.txt");
    for (int i = 0; i < map.getReceivers().size(); i++) {
        myfile << "Receiver " << i << std::endl;
        for (const std::pair<float, ComplexFloat> & p : results[i]) {
            myfile << p.first << " - " << p.second.toString() << std::endl;
        }
    }
    myfile << std::endl;
    myfile.close();

    delete[] results;
    if (!areSolutionTrianglesSaved) {
        std::cout << "Error: solution triangles were not saved!" << std::endl;
    }
    return solutionTriangles;
}

//private:
std::unique_ptr<std::list<RenderTriangle>> Solver::markAndCreateCubes(bool *** cubeMatrix, SolverPoint *** grid,
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
        //Mark cubes on triangle
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
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPNN, pointPPN, pointPPP, renT.getValue()));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPPP, pointPNP, pointPNN, renT.getValue()));
                        //Create -X plane
                        pointNPP.setTexPosition(0.f, 0.f);
                        pointNPN.setTexPosition(0.f, 1.f);
                        pointNNN.setTexPosition(1.f, 1.f);
                        pointNNP.setTexPosition(1.f, 0.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNPP, pointNPN, pointNNN, renT.getValue()));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNNN, pointNNP, pointNPP, renT.getValue()));
                        //Create +Y plane
                        pointNPP.setTexPosition(1.f, 0.f);
                        pointPPP.setTexPosition(0.f, 0.f);
                        pointPPN.setTexPosition(0.f, 1.f);
                        pointNPN.setTexPosition(1.f, 1.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNPP, pointPPP, pointPPN, renT.getValue()));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPPN, pointNPN, pointNPP, renT.getValue()));
                        //Create -Y plane
                        pointNNP.setTexPosition(0.f, 0.f);
                        pointPNP.setTexPosition(1.f, 0.f);
                        pointPNN.setTexPosition(1.f, 1.f);
                        pointNNN.setTexPosition(0.f, 1.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNNP, pointNNN, pointPNN, renT.getValue()));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPNN, pointPNP, pointNNP, renT.getValue()));
                        //Create +Z plane
                        pointNPP.setTexPosition(1.f, 1.f);
                        pointPPP.setTexPosition(0.f, 1.f);
                        pointPNP.setTexPosition(0.f, 0.f);
                        pointNNP.setTexPosition(1.f, 0.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNPP, pointNNP, pointPNP, renT.getValue()));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPNP, pointPPP, pointNPP, renT.getValue()));
                        //Create -Z plane
                        pointNPN.setTexPosition(0.f, 0.f);
                        pointPPN.setTexPosition(1.f, 0.f);
                        pointPNN.setTexPosition(1.f, 1.f);
                        pointNNN.setTexPosition(0.f, 1.f);
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointNPN, pointPPN, pointPNN, renT.getValue()));
                        cubeRenderTriangles.emplace_back(RenderTriangle(textureID, pointPNN, pointNNN, pointNPN, renT.getValue()));
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
                            grid[i][j][k].setToSource(renT.getValue());
                            grid[i+1][j][k].setToSource(renT.getValue());
                            grid[i][j+1][k].setToSource(renT.getValue());
                            grid[i+1][j+1][k].setToSource(renT.getValue());
                            grid[i][j][k+1].setToSource(renT.getValue());
                            grid[i+1][j][k+1].setToSource(renT.getValue());
                            grid[i][j+1][k+1].setToSource(renT.getValue());
                            grid[i+1][j+1][k+1].setToSource(renT.getValue());
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

                        glm::vec3 point0Position = pointPosition + _ARROW_SIZE * grid[i][j][k].getNormalVector();
                        glm::vec3 point11Position = pointPosition + _ARROW_SIZE/5 * firstSideVector;
                        glm::vec3 point12Position = pointPosition - _ARROW_SIZE/5 * firstSideVector;
                        glm::vec3 point21Position = pointPosition + _ARROW_SIZE/5 * secondSideVector;
                        glm::vec3 point22Position = pointPosition - _ARROW_SIZE/5 * secondSideVector;

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
        return std::unique_ptr<std::list<RenderTriangle>>(new std::list<RenderTriangle>(normalsRenderTriangles));
    } else {
        return std::unique_ptr<std::list<RenderTriangle>>(new std::list<RenderTriangle>(cubeRenderTriangles));
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

JacobiSystemOfEquations Solver::createSystemOfEquations(SolverPoint *** grid) const {
    //Reserve memory
    int numberOfVariables = (_pointMatrixSizeX+1)*(_pointMatrixSizeY+1)*(_pointMatrixSizeZ+1);
    std::cout << "Number of points: " << numberOfVariables << std::endl;
    JacobiSystemOfEquations systemOfEquations(2*numberOfVariables);

    //Fill equations
    std::cout << "\nEquations:" << std::endl;
    for (int k = 0; k < _pointMatrixSizeZ+1; k++) {
        for (int j = 0; j < _pointMatrixSizeY+1; j++) {
            for (int i = 0; i < _pointMatrixSizeX+1; i++) {
                int actRealID = calculateVariableIndex(i,j,k,false);
                int actImagID = calculateVariableIndex(i,j,k,true);
                if (grid[i][j][k].isSource()) {
                    //Source
                    const ComplexFloat & pressure = grid[i][j][k].getPressure();

                    //Real
                    systemOfEquations.set(actRealID, actRealID, 1.f);
                    systemOfEquations.setConstant(actRealID, pressure.real);
                    //Imag
                    systemOfEquations.set(actImagID, actImagID, 1.f);
                    systemOfEquations.setConstant(actImagID, pressure.imag);

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
                    //Borders
                    if (xm) {
                        if (ym) {
                            if (zm) {
                                //Corner XmYmZm
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Corner XmYmZp
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Edge XmYm
                                setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            }
                        } else if (yp) {
                            if (zm) {
                                //Corner XmYpZm
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Corner XmYpZp
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Edge XmYp
                                setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            }
                        } else {
                            if (zm) {
                                //Edge XmZm
                                setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Edge XmZp
                                setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Wall Xm
                                setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            }
                        }
                    } else if (xp) {
                        if (ym) {
                            if (zm) {
                                //Corner XpYmZm
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Corner XpYmZp
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Edge XpYm
                                setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            }
                        } else if (yp) {
                            if (zm) {
                                //Corner XpYpZm
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Corner XpYpZp
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Edge XpYp
                                setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            }
                        } else {
                            if (zm) {
                                //Edge XpZm
                                setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Edge XpZp
                                setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Wall Xp
                                setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            }
                        }
                    } else {
                        if (ym) {
                            if (zm) {
                                //Edge YmZm
                                setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Edge YmZp
                                setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Wall Ym
                                setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            }
                        } else if (yp) {
                            if (zm) {
                                //Edge YpZm
                                setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Edge YpZp
                                setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Wall Yp
                                setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            }
                        } else {
                            if (zm) {
                                //Wall Zm
                                setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else if (zp) {
                                //Wall Zp
                                setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
                                systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
                                systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                            } else {
                                //Not a border
                                glm::vec3 direction = grid[i][j][k].getNormalVector();
                                if (direction != glm::vec3(0,0,0)) {
                                    //Reflection
                                    //Find largest part
                                    DimensionName largestDimension = X;
                                    if (abs(direction.y) > abs(direction.x)) {
                                        if (abs(direction.z) > abs(direction.y)) {
                                            largestDimension = Z;
                                        } else {
                                            largestDimension = Y;
                                        }
                                    } else if (abs(direction.z) > abs(direction.x)) {
                                        largestDimension = Z;
                                    }
                                    //Scale normal vector
                                    switch (largestDimension) {
                                        case X: {
                                            direction *= _edgeLength / abs(direction.x);
                                            break;
                                        }
                                        case Y: {
                                            direction *= _edgeLength / abs(direction.y);
                                            break;
                                        }
                                        case Z: {
                                            direction *= _edgeLength / abs(direction.z);
                                            break;
                                        }
                                    }
//                                    std::cout << "Normal vector scaling:" << std::endl;
//                                    std::cout << grid[i][j][k].getNormalVector().x << " --> " << direction.x << std::endl;
//                                    std::cout << grid[i][j][k].getNormalVector().y << " --> " << direction.y << std::endl;
//                                    std::cout << grid[i][j][k].getNormalVector().z << " --> " << direction.z << std::endl;
                                    //Get square corner IDs and distances from edges
                                    int fixedI = i + pseudoSignum(direction.x);
                                    int fixedJ = j + pseudoSignum(direction.y);
                                    int fixedK = k + pseudoSignum(direction.z);
                                    int cornerXoYoRealID = calculateVariableIndex(fixedI, fixedJ, fixedK, false);
                                    int cornerXoYsRealID = -1;
                                    int cornerXsYoRealID = -1;
                                    int cornerXsYsRealID = -1;
                                    int cornerXoYoImagID = calculateVariableIndex(fixedI, fixedJ, fixedK, true);
                                    int cornerXoYsImagID = -1;
                                    int cornerXsYoImagID = -1;
                                    int cornerXsYsImagID = -1;
                                    float distXs = 0.f;
                                    float distYs = 0.f;
                                    switch (largestDimension) {
                                        case X: {
                                            cornerXoYsRealID = calculateVariableIndex(fixedI, fixedJ, k, false);
                                            cornerXsYoRealID = calculateVariableIndex(fixedI, j, fixedK, false);
                                            cornerXsYsRealID = calculateVariableIndex(fixedI, j, k, false);
                                            cornerXoYsImagID = calculateVariableIndex(fixedI, fixedJ, k, true);
                                            cornerXsYoImagID = calculateVariableIndex(fixedI, j, fixedK, true);
                                            cornerXsYsImagID = calculateVariableIndex(fixedI, j, k, true);
                                            distXs = abs(direction.y);
                                            distYs = abs(direction.z);
                                            break;
                                        }
                                        case Y: {
                                            cornerXoYsRealID = calculateVariableIndex(fixedI, fixedJ, k, false);
                                            cornerXsYoRealID = calculateVariableIndex(i, fixedJ, fixedK, false);
                                            cornerXsYsRealID = calculateVariableIndex(i, fixedJ, k, false);
                                            cornerXoYsImagID = calculateVariableIndex(fixedI, fixedJ, k, true);
                                            cornerXsYoImagID = calculateVariableIndex(i, fixedJ, fixedK, true);
                                            cornerXsYsImagID = calculateVariableIndex(i, fixedJ, k, true);
                                            distXs = abs(direction.x);
                                            distYs = abs(direction.z);
                                            break;
                                        }
                                        case Z: {
                                            cornerXoYsRealID = calculateVariableIndex(fixedI, j, fixedK, false);
                                            cornerXsYoRealID = calculateVariableIndex(i, fixedJ, fixedK, false);
                                            cornerXsYsRealID = calculateVariableIndex(i, j, fixedK, false);
                                            cornerXoYsImagID = calculateVariableIndex(fixedI, j, fixedK, true);
                                            cornerXsYoImagID = calculateVariableIndex(i, fixedJ, fixedK, true);
                                            cornerXsYsImagID = calculateVariableIndex(i, j, fixedK, true);
                                            distXs = abs(direction.x);
                                            distYs = abs(direction.y);
                                            break;
                                        }
                                    }
                                    assert(cornerXoYoRealID != cornerXoYsRealID != cornerXsYoRealID != cornerXsYsRealID !=
                                    cornerXoYoImagID != cornerXoYsImagID != cornerXsYoImagID != cornerXsYsImagID != actRealID != actImagID);
                                    float distXo = _edgeLength - distXs;
                                    float distYo = _edgeLength - distYs;
                                    //Calculate distances from corners
                                    float distXsYs = std::max(distXs, distYs);
                                    float distXsYo = std::max(distXs, distYo);
                                    float distXoYs = std::max(distXo, distYs);
                                    float distXoYo = std::max(distXo, distYo);
                                    //Set equation
                                    float directionLength = glm::length(direction);
                                    float denominator = directionLength * (4*_edgeLength - distXsYs - distXoYs - distXsYo - distXoYo);
                                    float oneOverDLength = (_edgeLength - distXsYs)/denominator +
                                            (_edgeLength - distXsYo)/denominator +
                                            (_edgeLength - distXoYs)/denominator +
                                            (_edgeLength - distXoYo)/denominator;
                                    //Real
                                    systemOfEquations.set(actRealID, actRealID, oneOverDLength);
                                    systemOfEquations.set(cornerXsYsRealID, actRealID, -(_edgeLength - distXsYs)/denominator);
                                    systemOfEquations.set(cornerXsYoRealID, actRealID, -(_edgeLength - distXsYo)/denominator);
                                    systemOfEquations.set(cornerXoYsRealID, actRealID, -(_edgeLength - distXoYs)/denominator);
                                    systemOfEquations.set(cornerXoYoRealID, actRealID, -(_edgeLength - distXoYo)/denominator);
                                    //Imag
                                    systemOfEquations.set(actImagID, actImagID, oneOverDLength);
                                    systemOfEquations.set(cornerXsYsImagID, actImagID, -(_edgeLength - distXsYs)/denominator);
                                    systemOfEquations.set(cornerXsYoImagID, actImagID, -(_edgeLength - distXsYo)/denominator);
                                    systemOfEquations.set(cornerXoYsImagID, actImagID, -(_edgeLength - distXoYs)/denominator);
                                    systemOfEquations.set(cornerXoYoImagID, actImagID, -(_edgeLength - distXoYo)/denominator);

                                } else {
                                    //Helmholtz equation
                                    setBorderX(systemOfEquations, actRealID, actImagID, i, j, k);
                                    setBorderY(systemOfEquations, actRealID, actImagID, i, j, k);
                                    setBorderZ(systemOfEquations, actRealID, actImagID, i, j, k);
                                    systemOfEquations.set(actRealID, actRealID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                    systemOfEquations.set(actImagID, actImagID, _edgeLength*_edgeLength*_waveLength*_waveLength - 6.f);
                                }
                            }
                        }
                    }
                }
//                systemOfEquations.print(actRealID);
//                systemOfEquations.print(actImagID);
            }
        }
    }

    return systemOfEquations;
}

int Solver::calculateVariableIndex(int i, int j, int k, bool b) const {
    if (b) return 2*((_pointMatrixSizeX + 1)*((_pointMatrixSizeY + 1)*k + j) + i) + 1;
    else return 2*((_pointMatrixSizeX + 1)*((_pointMatrixSizeY + 1)*k + j) + i);
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

void Solver::setBorder(JacobiSystemOfEquations & systemOfEquations, int actRealID, int actImagID,
               int neiRealID, int neiImagID, float constant) const {
    //Real
    systemOfEquations.set(actRealID, actRealID, 1.f);
    systemOfEquations.set(actImagID, actRealID, constant);
    systemOfEquations.set(neiImagID, actRealID, -constant);
    //Imag
    systemOfEquations.set(actImagID, actImagID, 1.f);
    systemOfEquations.set(actRealID, actImagID, constant);
    systemOfEquations.set(neiRealID, actImagID, -constant);
}
void Solver::setBorderX(JacobiSystemOfEquations & systemOfEquations, int actRealID, int actImagID, int i, int j, int k) const {
    //Real
    systemOfEquations.set(calculateVariableIndex(i+1,j,k,false), actRealID, 1.f);
    systemOfEquations.set(calculateVariableIndex(i-1,j,k,false), actRealID, 1.f);
    //Imag
    systemOfEquations.set(calculateVariableIndex(i+1,j,k,true), actImagID, 1.f);
    systemOfEquations.set(calculateVariableIndex(i-1,j,k,true), actImagID, 1.f);
}
void Solver::setBorderY(JacobiSystemOfEquations & systemOfEquations, int actRealID, int actImagID, int i, int j, int k) const {
    //Real
    systemOfEquations.set(calculateVariableIndex(i,j+1,k,false), actRealID, 1.f);
    systemOfEquations.set(calculateVariableIndex(i,j-1,k,false), actRealID, 1.f);
    //Imag
    systemOfEquations.set(calculateVariableIndex(i,j+1,k,true), actImagID, 1.f);
    systemOfEquations.set(calculateVariableIndex(i,j-1,k,true), actImagID, 1.f);
}
void Solver::setBorderZ(JacobiSystemOfEquations & systemOfEquations, int actRealID, int actImagID, int i, int j, int k) const {
    //Real
    systemOfEquations.set(calculateVariableIndex(i,j,k+1,false), actRealID, 1.f);
    systemOfEquations.set(calculateVariableIndex(i,j,k-1,false), actRealID, 1.f);
    //Imag
    systemOfEquations.set(calculateVariableIndex(i,j,k+1,true), actImagID, 1.f);
    systemOfEquations.set(calculateVariableIndex(i,j,k-1,true), actImagID, 1.f);
}
void Solver::createGrid(const Map & map, float frequency, int minNumberOfPointsPerPeriod) {
    //--- CREATE GRID ---//
    //Calculate constants
    _numberOfPointsPerPeriod = minNumberOfPointsPerPeriod - 1;
    const int MIN_GRID_SIZE = 3;
    do {
        _numberOfPointsPerPeriod++;
        _edgeLength = _SOUND_SPEED / (_numberOfPointsPerPeriod * frequency);
        //Find mins and maxs for grid (+1 point to avoid walls touching space borders)
        int borderLength = 0;
        _minX = map.getMinX() - borderLength * _edgeLength;
        _minY = map.getMinY() - borderLength * _edgeLength;
        _minZ = map.getMinZ() - borderLength * _edgeLength;
        _maxX = map.getMaxX() + borderLength * _edgeLength;
        _maxY = map.getMaxY() + borderLength * _edgeLength;
        _maxZ = map.getMaxZ() + borderLength * _edgeLength;
        //Create 3d point matrix
        _pointMatrixSizeX = int((_maxX - _minX) / _edgeLength) + 1;
        _pointMatrixSizeY = int((_maxY - _minY) / _edgeLength) + 1;
        _pointMatrixSizeZ = int((_maxZ - _minZ) / _edgeLength) + 1;
    } while (_pointMatrixSizeX < MIN_GRID_SIZE || _pointMatrixSizeY < MIN_GRID_SIZE || _pointMatrixSizeZ < MIN_GRID_SIZE);
    _angularFrequency = 2.f * _PI() * frequency;
    _waveLength = _angularFrequency / _SOUND_SPEED;
    std::cout << "Number of points per wave period: " << _numberOfPointsPerPeriod << std::endl;
    std::cout << "Edge length: " << _edgeLength << std::endl;
    std::cout << "Grid size: " << _pointMatrixSizeX << " - " << _pointMatrixSizeY << " - " << _pointMatrixSizeZ << std::endl;
    _grid = new SolverPoint ** [_pointMatrixSizeX + 1];
    for (int i = 0; i < _pointMatrixSizeX + 1; i++) {
        _grid[i] = new SolverPoint * [_pointMatrixSizeY + 1];
        for (int j = 0; j < _pointMatrixSizeY + 1; j++) {
            _grid[i][j] = new SolverPoint[_pointMatrixSizeZ + 1];
        }
    }
    //Create cube matrix
    _cubeMatrix = new bool ** [_pointMatrixSizeX];
    for (int i = 0; i < _pointMatrixSizeX; i++) {
        _cubeMatrix[i] = new bool * [_pointMatrixSizeY];
        for (int j = 0; j < _pointMatrixSizeY; j++) {
            _cubeMatrix[i][j] = new bool[_pointMatrixSizeZ];
            for (int k = 0; k < _pointMatrixSizeZ; k++) {
                _cubeMatrix[i][j][k] = false;
            }
        }
    }
}
void Solver::deleteGrid() const {
    for (int i = 0; i < _pointMatrixSizeX + 1; i++) {
        for (int j = 0; j < _pointMatrixSizeY + 1; j++) {
            delete[] _grid[i][j];
        }
        delete[] _grid[i];
    }
    delete[] _grid;
    for (int i = 0; i < _pointMatrixSizeX; i++) {
        for (int j = 0; j < _pointMatrixSizeY; j++) {
            delete[] _cubeMatrix[i][j];
        }
        delete[] _cubeMatrix[i];
    }
    delete[] _cubeMatrix;
}
std::unique_ptr<std::list<RenderTriangle>> Solver::createSolutionTriangles(const JacobiSystemOfEquations & equations,
        const SolverConfiguration & config, const std::list<RenderTriangle> & wallTriangles,
        const std::list<RenderTriangle> & speakerTriangles) const {
    //--- CREATE SOLUTION CUBES ---//
    std::cout << "Creating models:" << std::endl;
    //Create result array
    float * resultArray = new float[equations.getNumberOfVariables()/2];
    std::cout << "Length: " << equations.getNumberOfVariables()/2 << std::endl;
    switch (config.SCALE_TYPE) {
        case LINEAR: {
            switch (config.COMPLEX_TYPE) {
                case REAL: {
                    for (int i = 0; i < equations.getNumberOfVariables()/2; i++) {
                        resultArray[i] = equations.getSolution(2*i);
                        std::cout << resultArray[i] << '\t';
                    }
                    break;
                }
                case IMAG: {
                    for (int i = 0; i < equations.getNumberOfVariables()/2; i++) {
                        resultArray[i] = equations.getSolution(2*i+1);
                    }
                    break;
                }
                case ABS: {
                    for (int i = 0; i < equations.getNumberOfVariables()/2; i++) {
                        resultArray[i] = sqrt(equations.getSolution(2*i)*equations.getSolution(2*i) +
                                              equations.getSolution(2*i+1)*equations.getSolution(2*i+1));
                    }
                    break;
                }
            }
            break;
        }
        case DECIBELS: {
            switch (config.COMPLEX_TYPE) {
                case REAL: {
                    for (int i = 0; i < equations.getNumberOfVariables()/2; i++) {
                        resultArray[i] = 20 * std::log10(abs(equations.getSolution(2*i)) / _REFERENCE_PRESSURE);
                        if (std::isnan(resultArray[i]) || resultArray[i] < 0) {
                            resultArray[i] = 0;
                        }
                    }
                    break;
                }
                case IMAG: {
                    for (int i = 0; i < equations.getNumberOfVariables()/2; i++) {
                        resultArray[i] = 20 * std::log10(abs(equations.getSolution(2*i+1)) / _REFERENCE_PRESSURE);
                        if (std::isnan(resultArray[i]) || resultArray[i] < 0) {
                            resultArray[i] = 0;
                        }
                    }
                    break;
                }
                case ABS: {
                    for (int i = 0; i < equations.getNumberOfVariables()/2; i++) {
                        resultArray[i] = 20 * std::log10(sqrt(equations.getSolution(2*i)*equations.getSolution(2*i) +
                                                              equations.getSolution(2*i+1)*equations.getSolution(2*i+1)) / _REFERENCE_PRESSURE);
                        if (std::isnan(resultArray[i]) || resultArray[i] < 0) {
                            resultArray[i] = 0;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }

    //Find max and min results
    float maxResult = resultArray[0];
    float minResult = resultArray[0];
    for (int i = 0; i < equations.getNumberOfVariables()/2; i++) {
        if (!std::isinf(resultArray[i])) {
            float actResult = resultArray[i];
            if (actResult > maxResult) {
                maxResult = actResult;
            }
            if (actResult < minResult) {
                minResult = actResult;
            }
        }
    }
    std::cout << "\nVisualized result:" << std::endl;
    for (int i = 0; i < equations.getNumberOfVariables()/2; i++) {
        if (std::isinf(resultArray[i])) {
            if (resultArray[i] > 0) {
                resultArray[i] = maxResult;
            } else {
                resultArray[i] = minResult;
            }
        }
        std::cout << resultArray[i] << " \t";
    }
    std::cout << "\nMax result: " << maxResult << std::endl;
    maxResult *= 1.02f; //To prevent blending with other textures
    std::cout << "Min result: " << minResult << std::endl;
    minResult *= 1.01f; //To prevent blending with other textures
    std::cout << std::endl;

    //Create triangles
    std::list<RenderTriangle> solutionTriangles;
    for (int ix = 0; ix < _pointMatrixSizeX + 1; ix++) {
        for (int iy = 0; iy < _pointMatrixSizeY + 1; iy++) {
            for (int iz = 0; iz < _pointMatrixSizeZ + 1; iz++) {
                //Trangle corners
                glm::vec3 pointCenter = glm::vec3((ix * _edgeLength) + _minX, (iy * _edgeLength) + _minY, (iz * _edgeLength) + _minZ);
                float colorValue = (resultArray[calculateVariableIndex(ix, iy, iz, false)/2] - minResult) / (maxResult - minResult);
                RenderVertex cornerXp = RenderVertex(glm::vec3(pointCenter + glm::vec3(config.DOT_SIZE, 0, 0)), colorValue, colorValue);
                RenderVertex cornerXm = RenderVertex(glm::vec3(pointCenter + glm::vec3(-config.DOT_SIZE, 0, 0)), colorValue, colorValue);
                RenderVertex cornerYp = RenderVertex(glm::vec3(pointCenter + glm::vec3(0, config.DOT_SIZE, 0)), colorValue, colorValue);
                RenderVertex cornerYm = RenderVertex(glm::vec3(pointCenter + glm::vec3(0, -config.DOT_SIZE, 0)), colorValue, colorValue);
                RenderVertex cornerZp = RenderVertex(glm::vec3(pointCenter + glm::vec3(0, 0, config.DOT_SIZE)), colorValue, colorValue);
                RenderVertex cornerZm = RenderVertex(glm::vec3(pointCenter + glm::vec3(0, 0, -config.DOT_SIZE)), colorValue, colorValue);
                //Create triangles
                solutionTriangles.emplace_back(RenderTriangle(TextureType::COLOR, cornerXp, cornerYp, cornerZp));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::COLOR, cornerZp, cornerYp, cornerXm));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::COLOR, cornerZp, cornerYm, cornerXp));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::COLOR, cornerXm, cornerYm, cornerZp));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::COLOR, cornerZm, cornerYp, cornerXp));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::COLOR, cornerXm, cornerYp, cornerZm));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::COLOR, cornerXp, cornerYm, cornerZm));
                solutionTriangles.emplace_back(RenderTriangle(TextureType::COLOR, cornerZm, cornerYm, cornerXm));
            }
        }
    }
    //Cleanup
    delete[] resultArray;
    //Concatenate triangles
    solutionTriangles.insert(solutionTriangles.end(), wallTriangles.begin(), wallTriangles.end());
    solutionTriangles.insert(solutionTriangles.end(), speakerTriangles.begin(), speakerTriangles.end());

    return std::unique_ptr<std::list<RenderTriangle>>(new std::list<RenderTriangle>(solutionTriangles));
//    return cubeTriangles;
}
