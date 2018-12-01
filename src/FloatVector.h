//
// Created by baronvladziu on 03.11.18.
//

#ifndef VULKAN_FDM_COMPLEXVECTOR_H
#define VULKAN_FDM_COMPLEXVECTOR_H

#include "header.h"
#include "ComplexFloat.h"


class FloatVector {

    int _size = 0;
    std::unordered_map<int, float> _values;

public:
    FloatVector();
    explicit FloatVector(int size);
    void resetSize(int size);
    FloatVector(const FloatVector & v);
    int getSize() const;
    float get(int i) const;
    void set(int i, float value);
    float getMax() const;
    float getMaxAbs() const;
    float getMin() const;
    float getSum() const;
    float getAbsSum() const;
    float getNorm() const;
    void fillWithZeros();
    void randomize(float maxValue);
    void randomize(float minValue, float maxValue);
    void randomize(int i, float minValue, float maxValue);
    FloatVector & operator=(const FloatVector & v);
    FloatVector operator+(const FloatVector & v) const;
    FloatVector operator-(const FloatVector & v) const;
    float operator*(const FloatVector & v) const;
    FloatVector operator*(float k) const;
    FloatVector operator/(float k) const;
    void operator+=(const FloatVector & v);
    void operator-=(const FloatVector & v);
    void operator*=(float k);
    void operator/=(float k);
    bool operator==(const FloatVector & v) const;
    bool operator!=(const FloatVector & v) const;
    void print() const;
    void sparsePrint() const;
    void print(const std::string & filename) const;

};


#endif //VULKAN_FDM_COMPLEXVECTOR_H
