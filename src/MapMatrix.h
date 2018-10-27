//
// Created by baronvladziu on 26.10.18.
//

#ifndef VULKAN_FDM_MAPMATRIX_H
#define VULKAN_FDM_MAPMATRIX_H

#include "header.h"
#include "ComplexFloat.h"
#include "MapValue.h"


class MapMatrix {

    int _sizeX = 0;
    int _sizeY = 0;
    std::unordered_map<int, ComplexFloat> * _values = nullptr;

public:
    MapMatrix(int x, int y);
    MapMatrix(const MapMatrix & m);
    int getX() const;
    int getY() const;
    ComplexFloat get(int x, int y) const;
    const std::unordered_map<int, ComplexFloat> & getValues(int y) const;
    void set(int x, int y, const ComplexFloat & value);
    ComplexFloat getMax() const;
    void fillWithZeros();
    MapMatrix extractUpper() const;
    MapMatrix extractDiagonal() const;
    MapMatrix extractLower() const;
    MapMatrix & operator=(const MapMatrix & m);
    MapMatrix operator+(const MapMatrix & m) const;
    MapMatrix operator-(const MapMatrix & m) const;
    MapMatrix operator*(const MapMatrix & m) const;
    MapMatrix operator*(const ComplexFloat & k) const;
    void operator/=(float k);
    void operator/=(const ComplexFloat & k);
    bool operator==(const MapMatrix & m) const;
    bool operator!=(const MapMatrix & m) const;
    MapMatrix extractDiagonalInverse() const;
    void print() const;
    void print(const std::string & filename) const;
    ~MapMatrix();

private:
    void cleanup();

};


#endif //VULKAN_FDM_MAPMATRIX_H
