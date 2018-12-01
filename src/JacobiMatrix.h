//
// Created by baronvladziu on 30.11.18.
//

#ifndef VULKAN_FDM_JACOBIMATRIX_H
#define VULKAN_FDM_JACOBIMATRIX_H

#include "header.h"


class JacobiMatrix {

    int _sizeX = 0;
    int _sizeY = 0;
    std::unordered_map<int, float> * _values = nullptr;

public:
    JacobiMatrix(int x, int y);
    JacobiMatrix(const JacobiMatrix & m);
    int getX() const;
    int getY() const;
    float get(int x, int y) const;
    const std::unordered_map<int, float> & getValues(int y) const;
    void set(int x, int y, float value);
    float getMax() const;
    void fillWithZeros();
    void randomize();
    JacobiMatrix extractUpper() const;
    JacobiMatrix extractDiagonal() const;
    JacobiMatrix extractLower() const;
    JacobiMatrix & operator=(const JacobiMatrix & m);
    JacobiMatrix operator+(const JacobiMatrix & m) const;
    JacobiMatrix operator-(const JacobiMatrix & m) const;
    JacobiMatrix operator*(const JacobiMatrix & m) const;
    JacobiMatrix operator*(float k) const;
    void operator/=(float k);
    bool operator==(const JacobiMatrix & m) const;
    bool operator!=(const JacobiMatrix & m) const;
    JacobiMatrix extractDiagonalInverse() const;
    void print() const;
    void print(const std::string & filename) const;
    ~JacobiMatrix();

private:
    void cleanup();

};


#endif //VULKAN_FDM_JACOBIMATRIX_H
