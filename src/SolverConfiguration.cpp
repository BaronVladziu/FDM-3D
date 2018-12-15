//
// Created by baronvladziu on 01.12.18.
//

#include "SolverConfiguration.h"

SolverConfiguration::SolverConfiguration(const std::string & configPath) {
    std::cout << "--- PARSING CONFIG FILE ---" << std::endl;
    SolverConfigurationState state = WAITING_FOR_CONFIG_FILE_START;
    std::fstream file;
    file.open(configPath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Failed to find or open " + configPath + " !");
    }
    std::string word;
    while (file >> word) {
        switch (state) {
            case WAITING_FOR_CONFIG_FILE_START: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {}
                else if (word == "\"config\":") {
                    state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                } else {
                    throw std::runtime_error("Error: Tried to load config from file " + configPath +
                                             " but it does not seem to be config json file!");
                }
                break;
            }
            case WAITING_FOR_CONFIG_ANOTHER_VALUE: {
                if (word == "{") {}
                else if (word == "}" || word == "},") {
                    state = WAITING_FOR_CONFIG_FILE_END;
                } else if (word == "\"modelName\":") {
                    state = WAITING_FOR_CONFIG_MODEL_NAME;
                } else if (word == "\"minimalNumberOfPointsPerPeriod\":") {
                    state = WAITING_FOR_CONFIG_MINIMAL_NUMBER_OF_POINTS_PER_PERIOD;
                } else if (word == "\"dotSize\":") {
                    state = WAITING_FOR_CONFIG_DOT_SIZE;
                } else if (word == "\"startFrequency\":") {
                    state = WAITING_FOR_CONFIG_START_FREQUENCY;
                } else if (word == "\"endFrequency\":") {
                    state = WAITING_FOR_CONFIG_STOP_FREQUENCY;
                } else if (word == "\"mainFrequency\":") {
                    state = WAITING_FOR_CONFIG_MAIN_FREQUENCY;
                } else if (word == "\"complexType\":") {
                    state = WAITING_FOR_CONFIG_COMPLEX_TYPE;
                } else if (word == "\"scaleType\":") {
                    state = WAITING_FOR_CONFIG_SCALE_TYPE;
                } else {
                    throw std::runtime_error(
                            "Error: While loading file " + configPath + " , unknown point parameter: " + word +
                            " !");
                }
                break;
            }
            case WAITING_FOR_CONFIG_MODEL_NAME: {
                std::string strValue = word;
                strValue.pop_back();
                strValue.pop_back();
                MODEL_NAME = strValue.substr(1, strValue.size() - 1);
                state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                break;
            }
            case WAITING_FOR_CONFIG_MINIMAL_NUMBER_OF_POINTS_PER_PERIOD: {
                std::string strValue = word;
                strValue.pop_back();
                int value = std::stoi(strValue);
                MINIMAL_NUMBER_OF_POINTS_PER_PERIOD = value;
                state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                break;
            }
            case WAITING_FOR_CONFIG_DOT_SIZE: {
                std::string strValue = word;
                strValue.pop_back();
                float value = std::stof(strValue);
                DOT_SIZE = value;
                state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                break;
            }
            case WAITING_FOR_CONFIG_START_FREQUENCY: {
                std::string strValue = word;
                strValue.pop_back();
                float value = std::stof(strValue);
                START_FREQUENCY = value;
                state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                break;
            }
            case WAITING_FOR_CONFIG_STOP_FREQUENCY: {
                std::string strValue = word;
                strValue.pop_back();
                float value = std::stof(strValue);
                STOP_FREQUENCY = value;
                state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                break;
            }
            case WAITING_FOR_CONFIG_MAIN_FREQUENCY: {
                std::string strValue = word;
                strValue.pop_back();
                float value = std::stof(strValue);
                MAIN_FREQUENCY = value;
                state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                break;
            }
            case WAITING_FOR_CONFIG_COMPLEX_TYPE: {
                std::string strValue = word;
                strValue.pop_back();
                if (strValue == "\"real\"") COMPLEX_TYPE = Complex2RealType::REAL;
                else if (strValue == "\"imag\"") COMPLEX_TYPE = Complex2RealType::IMAG;
                else if (strValue == "\"abs\"") COMPLEX_TYPE = Complex2RealType::ABS;
                else throw std::runtime_error("Error: While loading file " + configPath + " , unknown complexType!");
                state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                break;
            }
            case WAITING_FOR_CONFIG_SCALE_TYPE: {
                std::string strValue = word;
                strValue.pop_back();
                if (strValue == "\"linear") SCALE_TYPE = ScaleType::LINEAR;
                else if (strValue == "\"decibels") SCALE_TYPE = ScaleType::DECIBELS;
                else throw std::runtime_error("Error: While loading file " + configPath + " , unknown scaleType!");
                state = WAITING_FOR_CONFIG_ANOTHER_VALUE;
                break;
            }
            case WAITING_FOR_CONFIG_FILE_END: {
                break;
            }
            default: {
                throw std::runtime_error(
                        "Error: While loading file " + configPath + " , unknown MapLoaderState!");
                break;
            }
        }
    }
    file.close();
    std::cout << "Model name: " << MODEL_NAME << std::endl;
}