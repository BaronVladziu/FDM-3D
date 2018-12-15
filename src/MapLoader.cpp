//
// Created by baronvladziu on 08.09.18.
//

#include "MapLoader.h"

Map MapLoader::loadMap(const std::string & wallsJsonPath, const std::string & speakersJsonPath,
                       const std::string & receiversJsonPath) const {
    std::cout << "\n --- PARSING MAP FILES ---" << std::endl;
    Map resultMap;
    Range3D ranges = loadWalls(resultMap, wallsJsonPath);
    ranges += loadSpeakers(resultMap, speakersJsonPath);
    ranges += loadReceivers(resultMap, receiversJsonPath);

    resultMap.setRanges(ranges);
    return resultMap;
}

Range3D MapLoader::loadWalls(Map & resultMap, const std::string & wallsJsonPath) const {
    float minX = 0.f;
    float minY = 0.f;
    float minZ = 0.f;
    float maxX = 0.f;
    float maxY = 0.f;
    float maxZ = 0.f;

    RenderVertex actVertex;
    int idA = 0;
    int idB = 0;
    int idC = 0;

    MapLoaderState state = WAITING_FOR_FILE_START;
    std::fstream file;
    file.open(wallsJsonPath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Failed to find or open " + wallsJsonPath + " !");
    }
    std::vector<RenderVertex> vertices;
    std::string word;
    while (file >> word) {
        switch (state) {
            case WAITING_FOR_FILE_START: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {}
                else if (word == "\"map\":") {
                    state = WAITING_FOR_POINTS_START;
                }
                else {
                    throw std::runtime_error("Error: Tried to load map from file " + wallsJsonPath +
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
                            "Error: While loading file " + wallsJsonPath + " , expected \"points\": and got " + word +
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
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + wallsJsonPath + " , unknown point parameter: " + word +
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
                            "Error: While loading file " + wallsJsonPath + " , expected id = " +
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
                float value = std::stof(strValue);
                actVertex.setZ(value);
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
                            "Error: While loading file " + wallsJsonPath + " , expected \"triangles\": and got " + word +
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
                            "Error: While loading file " + wallsJsonPath + " , unknown triangle parameter: " + word +
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
                            "Error: While loading file " + wallsJsonPath + " , found point id: " + strValue +
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
                            "Error: While loading file " + wallsJsonPath + " , found point id: " + strValue +
                            " that is out of range!");
                }
                break;
            }
            case WAITING_FOR_TRIANGLE_C: {
                std::string strValue = word;
                int value = std::stoi(strValue);
                if (value < vertices.size()) {
                    idC = value;
                    resultMap.addWallTriange(RenderTriangle(TextureType::WALL, vertices[idA], vertices[idB], vertices[idC]));
                    state = WAITING_FOR_ANOTHER_TRIANGLE_VALUE;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + wallsJsonPath + " , found point id: " + strValue +
                            " that is out of range!");
                }
                break;
            }
            case WAITING_FOR_FILE_END: {
                break;
            }
            default: {
                throw std::runtime_error(
                        "Error: While loading file " + wallsJsonPath + " , unknown MapLoaderState!");
                break;
            }
        }
    }
    file.close();

    //Find borders
    for (const RenderVertex v : vertices) {
        if (v.getX() < minX) minX = v.getX();
        if (v.getX() > maxX) maxX = v.getX();
        if (v.getY() < minY) minY = v.getY();
        if (v.getY() > maxY) maxY = v.getY();
        if (v.getZ() < minZ) minZ = v.getZ();
        if (v.getZ() > maxZ) maxZ = v.getZ();
    }

    return Range3D(minX, minY, minZ, maxX, maxY, maxZ);
}

Range3D MapLoader::loadSpeakers(Map & resultMap, const std::string & speakersJsonPath) const {
    float minX = 0.f;
    float minY = 0.f;
    float minZ = 0.f;
    float maxX = 0.f;
    float maxY = 0.f;
    float maxZ = 0.f;

    RenderVertex actVertex;
    int idA = 0;
    int idB = 0;
    int idC = 0;
    ComplexFloat volume;

    MapLoaderState state = WAITING_FOR_FILE_START;
    std::fstream file;
    file.open(speakersJsonPath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Failed to find or open " + speakersJsonPath + " !");
    }
    std::vector<RenderVertex> vertices;
    std::string word;
    while (file >> word) {
        switch (state) {
            case WAITING_FOR_FILE_START: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {}
                else if (word == "\"speakers\":") {
                    state = WAITING_FOR_POINTS_START;
                }
                else {
                    throw std::runtime_error("Error: Tried to load map from file " + speakersJsonPath +
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
                            "Error: While loading file " + speakersJsonPath + " , expected \"points\": and got " + word +
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
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + speakersJsonPath + " , unknown point parameter: " + word +
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
                            "Error: While loading file " + speakersJsonPath + " , expected id = " +
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
                float value = std::stof(strValue);
                actVertex.setZ(value);
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
                            "Error: While loading file " + speakersJsonPath + " , expected \"triangles\": and got " + word +
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
                else if (word == "\"volumeR\":") {
                    state = WAITING_FOR_SPEAKER_VOLUME_R;
                }
                else if (word == "\"volumeI\":") {
                    state = WAITING_FOR_SPEAKER_VOLUME_I;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + speakersJsonPath + " , unknown triangle parameter: " + word +
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
                            "Error: While loading file " + speakersJsonPath + " , found point id: " + strValue +
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
                            "Error: While loading file " + speakersJsonPath + " , found point id: " + strValue +
                            " that is out of range!");
                }
                break;
            }
            case WAITING_FOR_TRIANGLE_C: {
                std::string strValue = word;
                int value = std::stoi(strValue);
                if (value < vertices.size()) {
                    idC = value;
                    state = WAITING_FOR_ANOTHER_TRIANGLE_VALUE;
                }
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + speakersJsonPath + " , found point id: " + strValue +
                            " that is out of range!");
                }
                break;
            }
            case WAITING_FOR_SPEAKER_VOLUME_R: {
                std::string strValue = word;
                float value = std::stof(strValue);
                volume.imag = value;
                state = WAITING_FOR_ANOTHER_TRIANGLE_VALUE;
                break;
            }
            case WAITING_FOR_SPEAKER_VOLUME_I: {
                std::string strValue = word;
                float value = std::stof(strValue);
                volume.imag = value;
                if (volume == ComplexFloat(0,0)) {
                    std::cout << "Warning: No value loaded for speaker!" << std::endl;
                }
                resultMap.addSpeakerTriange(RenderTriangle(TextureType::SPEAKER, vertices[idA], vertices[idB], vertices[idC], volume));
                state = WAITING_FOR_ANOTHER_TRIANGLE_VALUE;
                break;
            }
            case WAITING_FOR_FILE_END: {
                break;
            }
            default: {
                throw std::runtime_error(
                        "Error: While loading file " + speakersJsonPath + " , unknown MapLoaderState!");
                break;
            }
        }
    }
    file.close();

    if (vertices.size() == 0) {
        std::cout << "Error: No speaker vertices loaded!" << std::endl;
    }
    if (resultMap.getSpeakerTriangles().size() == 0) {
        std::cout << "Error: No speaker triangles loaded!" << std::endl;
    }

    //Find borders
    for (const RenderVertex v : vertices) {
        if (v.getX() < minX) minX = v.getX();
        if (v.getX() > maxX) maxX = v.getX();
        if (v.getY() < minY) minY = v.getY();
        if (v.getY() > maxY) maxY = v.getY();
        if (v.getZ() < minZ) minZ = v.getZ();
        if (v.getZ() > maxZ) maxZ = v.getZ();
    }

    return Range3D(minX, minY, minZ, maxX, maxY, maxZ);
}
Range3D MapLoader::loadReceivers(Map & resultMap, const std::string & receiversJsonPath) const {
    float minX = 0.f;
    float minY = 0.f;
    float minZ = 0.f;
    float maxX = 0.f;
    float maxY = 0.f;
    float maxZ = 0.f;

    RenderVertex actVertex;
    int idA = 0;
    int idB = 0;
    int idC = 0;

    MapLoaderState state = WAITING_FOR_FILE_START;
    std::fstream file;
    file.open(receiversJsonPath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Failed to find or open " + receiversJsonPath + " !");
    }
    std::vector<RenderVertex> vertices;
    std::string word;
    while (file >> word) {
        switch (state) {
            case WAITING_FOR_FILE_START: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {}
                else if (word == "\"receivers\":") {
                    state = WAITING_FOR_POINTS_START;
                }
                else {
                    throw std::runtime_error("Error: Tried to load map from file " + receiversJsonPath +
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
                            "Error: While loading file " + receiversJsonPath + " , expected \"points\": and got " + word +
                            " !");
                }
                break;
            }
            case WAITING_FOR_ANOTHER_POINT_VALUE: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "[") {}
                else if (word == "]" || word == "],") {
                    state = WAITING_FOR_FILE_END;
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
                else {
                    throw std::runtime_error(
                            "Error: While loading file " + receiversJsonPath + " , unknown point parameter: " + word +
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
                float value = std::stof(strValue);
                actVertex.setZ(value);
                resultMap.addReceiver(actVertex);
                state = WAITING_FOR_ANOTHER_POINT_VALUE;
                break;
            }
            case WAITING_FOR_FILE_END: {
                break;
            }
            default: {
                throw std::runtime_error(
                        "Error: While loading file " + receiversJsonPath + " , unknown MapLoaderState!");
                break;
            }
        }
    }
    file.close();

    //Find borders
    for (const RenderVertex v : vertices) {
        if (v.getX() < minX) minX = v.getX();
        if (v.getX() > maxX) maxX = v.getX();
        if (v.getY() < minY) minY = v.getY();
        if (v.getY() > maxY) maxY = v.getY();
        if (v.getZ() < minZ) minZ = v.getZ();
        if (v.getZ() > maxZ) maxZ = v.getZ();
    }

    return Range3D(minX, minY, minZ, maxX, maxY, maxZ);
}