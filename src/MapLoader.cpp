//
// Created by baronvladziu on 08.09.18.
//

#include "MapLoader.h"

Map MapLoader::loadMap(const std::string & mapJsonPath) const {
    MapLoaderState state = WAITING_FOR_MAP_START;
    std::fstream file;
    file.open(mapJsonPath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Failed to find or open " + mapJsonPath + " !");
    }
    Map resultMap;
    std::vector<RenderVertex> vertices;

    RenderVertex actVertex;
    int idA = 0;
    int idB = 0;
    int idC = 0;
    std::string word;
    while (file >> word) {
        switch (state) {
            case WAITING_FOR_MAP_START: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {}
                else if (word == "\"map\":") {
                    state = WAITING_FOR_POINTS_START;
                }
                else {
                    throw std::runtime_error("Error: Tried to load map from file " + mapJsonPath +
                                             " but it does not seem to be map json file!");
                }
                break;
            }
            case WAITING_FOR_POINTS_START: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {}
                else if (word == "\"points\":") {
                    state = WAITING_FOR_ANOTHER_POINT_VALUE;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + mapJsonPath + " , expected \"points\": and got " + word +
                            " !");
                }
                break;
            }
            case WAITING_FOR_ANOTHER_POINT_VALUE: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {
                    state = WAITING_FOR_TRIANGLES_START;
                }
                else if (word == "\"id\":") {
                    state = WAITING_FOR_POINT_ID;
                }
                else if (word == "\"x\":") {
                    state = WAITING_FOR_POINT_X;
                }
                else if (word == "\"y\":") {
                    state = WAITING_FOR_POINT_Y;
                }
                else if (word == "\"z\":") {
                    state = WAITING_FOR_POINT_Z;
                }
                else if (word == "\"texX\":") {
                    state = WAITING_FOR_POINT_TEX_X;
                }
                else if (word == "\"texY\":") {
                    state = WAITING_FOR_POINT_TEX_Y;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + mapJsonPath + " , unknown point parameter: " + word +
                            " !");
                }
                break;
            }
            case WAITING_FOR_POINT_ID: {
                std::string strValue = word;
                strValue.pop_back();
                int value = std::stoi(strValue);
                if (value == vertices.size()) {
                    state = WAITING_FOR_ANOTHER_POINT_VALUE;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + mapJsonPath + " , expected id = " +
                            std::to_string(vertices.size()) +
                            " and got " + strValue +
                            " !");
                }
                break;
            }
            case WAITING_FOR_POINT_X: {
                std::string strValue = word;
                strValue.pop_back();
                float value = std::stof(strValue);
                actVertex.setX(value);
                state = WAITING_FOR_ANOTHER_POINT_VALUE;
                break;
            }
            case WAITING_FOR_POINT_Y: {
                std::string strValue = word;
                strValue.pop_back();
                float value = std::stof(strValue);
                actVertex.setY(value);
                state = WAITING_FOR_ANOTHER_POINT_VALUE;
                break;
            }
            case WAITING_FOR_POINT_Z: {
                std::string strValue = word;
                strValue.pop_back();
                float value = std::stof(strValue);
                actVertex.setZ(value);
                state = WAITING_FOR_ANOTHER_POINT_VALUE;
                break;
            }
            case WAITING_FOR_POINT_TEX_X: {
                std::string strValue = word;
                strValue.pop_back();
                float value = std::stof(strValue);
                actVertex.setTexX(value);
                state = WAITING_FOR_ANOTHER_POINT_VALUE;
                break;
            }
            case WAITING_FOR_POINT_TEX_Y: {
                std::string strValue = word;
                float value = std::stof(strValue);
                actVertex.setTexY(value);
                vertices.push_back(actVertex);
                state = WAITING_FOR_ANOTHER_POINT_VALUE;
                break;
            }
            case WAITING_FOR_TRIANGLES_START: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {}
                else if (word == "\"triangles\":") {
                    state = WAITING_FOR_ANOTHER_TRIANGLE_VALUE;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + mapJsonPath + " , expected \"triangles\": and got " + word +
                            " !");
                }
                break;
            }
            case WAITING_FOR_ANOTHER_TRIANGLE_VALUE: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {
                    state = WAITING_FOR_FILE_END;
                }
                else if (word == "\"v1\":") {
                    state = WAITING_FOR_TRIANGLE_A;
                }
                else if (word == "\"v2\":") {
                    state = WAITING_FOR_TRIANGLE_B;
                }
                else if (word == "\"v3\":") {
                    state = WAITING_FOR_TRIANGLE_C;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + mapJsonPath + " , unknown triangle parameter: " + word +
                            " !");
                }
                break;
            }
            case WAITING_FOR_TRIANGLE_A: {
                std::string strValue = word;
                strValue.pop_back();
                int value = std::stoi(strValue);
                if (value < vertices.size()) {
                    idA = value;
                    state = WAITING_FOR_ANOTHER_TRIANGLE_VALUE;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + mapJsonPath + " , found point id: " + strValue +
                            " that is out of range!");
                }
                break;
            }
            case WAITING_FOR_TRIANGLE_B: {
                std::string strValue = word;
                strValue.pop_back();
                int value = std::stoi(strValue);
                if (value < vertices.size()) {
                    idB = value;
                    state = WAITING_FOR_ANOTHER_TRIANGLE_VALUE;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + mapJsonPath + " , found point id: " + strValue +
                            " that is out of range!");
                }
                break;
            }
            case WAITING_FOR_TRIANGLE_C: {
                std::string strValue = word;
                int value = std::stoi(strValue);
                if (value < vertices.size()) {
                    idC = value;
                    resultMap.addRenderTriange(RenderTriangle(vertices[idA], vertices[idB], vertices[idC]));
                    state = WAITING_FOR_ANOTHER_TRIANGLE_VALUE;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + mapJsonPath + " , found point id: " + strValue +
                            " that is out of range!");
                }
                break;
            }
            case WAITING_FOR_FILE_END: {
                break;
            }
            default: {
                throw std::runtime_error(
                        "Error: While loading file " + mapJsonPath + " , unknown MapLoaderState!");
                break;
            }
        }
    }

    return resultMap;
}
