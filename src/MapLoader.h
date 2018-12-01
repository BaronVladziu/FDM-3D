//
// Created by baronvladziu on 08.09.18.
//

#ifndef VULKAN_FDM_MAPLOADER_H
#define VULKAN_FDM_MAPLOADER_H

#include "header.h"
#include "Map.h"
#include "Range3D.h"


enum MapLoaderState {
    WAITING_FOR_FILE_START, //0
    WAITING_FOR_POINTS_START, //1
    WAITING_FOR_ANOTHER_POINT_VALUE, //2
    WAITING_FOR_POINT_ID, //3
    WAITING_FOR_POINT_X, //4
    WAITING_FOR_POINT_Y, //5
    WAITING_FOR_POINT_Z, //6
    WAITING_FOR_POINT_TEX_X, //7
    WAITING_FOR_POINT_TEX_Y, //8
    WAITING_FOR_TRIANGLES_START, //9
    WAITING_FOR_ANOTHER_TRIANGLE_VALUE, //10
    WAITING_FOR_TRIANGLE_A, //11
    WAITING_FOR_TRIANGLE_B, //12
    WAITING_FOR_TRIANGLE_C, //13
    WAITING_FOR_FILE_END, //14
    WAITING_FOR_SPEAKER_VOLUME_R, //15
    WAITING_FOR_SPEAKER_VOLUME_I //16
};


class MapLoader {

public:
    Map loadMap(const std::string & wallsJsonPath, const std::string & speakersJsonPath,
                const std::string & receiversJsonPath) const;

private:
    Range3D loadWalls(Map & resultMap, const std::string & wallsJsonPath) const;
    Range3D loadSpeakers(Map & resultMap, const std::string & speakersJsonPath) const;
    Range3D loadReceivers(Map & resultMap, const std::string & receiversJsonPath) const;

};


#endif //VULKAN_FDM_MAPLOADER_H
