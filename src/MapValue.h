//
// Created by baronvladziu on 26.10.18.
//

#ifndef VULKAN_FDM_MAPVALUE_H
#define VULKAN_FDM_MAPVALUE_H

#include "ComplexFloat.h"


class MapValue {

public:
    int id;
    ComplexFloat value;

    MapValue(const std::pair<int, ComplexFloat> & pair)
        : id(pair.first), value(pair.second)
    {}

};


#endif //VULKAN_FDM_MAPVALUE_H
