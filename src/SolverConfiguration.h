//
// Created by baronvladziu on 01.12.18.
//

#ifndef VULKAN_FDM_SOLVERCONFIGURATION_H
#define VULKAN_FDM_SOLVERCONFIGURATION_H


#include "header.h"
#include "Complex2RealType.h"
#include "ScaleType.h"

enum SolverConfigurationState {
    WAITING_FOR_CONFIG_FILE_START, //0
    WAITING_FOR_CONFIG_ANOTHER_VALUE, //1
    WAITING_FOR_CONFIG_MINIMAL_NUMBER_OF_POINTS_PER_PERIOD, //2
    WAITING_FOR_CONFIG_DOT_SIZE, //3
    WAITING_FOR_CONFIG_START_FREQUENCY, //4
    WAITING_FOR_CONFIG_STOP_FREQUENCY, //5
    WAITING_FOR_CONFIG_MAIN_FREQUENCY, //6
    WAITING_FOR_CONFIG_COMPLEX_TYPE, //7
    WAITING_FOR_CONFIG_SCALE_TYPE, //8
    WAITING_FOR_CONFIG_FILE_END //9
};

class SolverConfiguration {

public:
    int MINIMAL_NUMBER_OF_POINTS_PER_PERIOD = 8;
    float DOT_SIZE = 0.06f;
    float START_FREQUENCY = 0.f;
    float STOP_FREQUENCY = 0.f;
    float MAIN_FREQUENCY = 350.f;
    Complex2RealType COMPLEX_TYPE = Complex2RealType::IMAG;
    ScaleType SCALE_TYPE = ScaleType::DECIBELS;

    SolverConfiguration() = default;
    SolverConfiguration(const std::string & configPath);

};


#endif //VULKAN_FDM_SOLVERCONFIGURATION_H
