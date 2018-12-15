//
// Created by baronvladziu on 01.12.18.
//

#ifndef VULKAN_FDM_SOLVERCONFIGURATION_H
#define VULKAN_FDM_SOLVERCONFIGURATION_H


#include "header.h"
#include "Complex2RealType.h"
#include "ScaleType.h"

enum SolverConfigurationState {
    WAITING_FOR_CONFIG_FILE_START,
    WAITING_FOR_CONFIG_ANOTHER_VALUE,
    WAITING_FOR_CONFIG_MODEL_NAME,
    WAITING_FOR_CONFIG_MINIMAL_NUMBER_OF_POINTS_PER_PERIOD,
    WAITING_FOR_CONFIG_DOT_SIZE,
    WAITING_FOR_CONFIG_START_FREQUENCY,
    WAITING_FOR_CONFIG_STOP_FREQUENCY,
    WAITING_FOR_CONFIG_MAIN_FREQUENCY,
    WAITING_FOR_CONFIG_COMPLEX_TYPE,
    WAITING_FOR_CONFIG_SCALE_TYPE,
    WAITING_FOR_CONFIG_FILE_END
};

class SolverConfiguration {

public:
    std::string MODEL_NAME = "testModel";
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
