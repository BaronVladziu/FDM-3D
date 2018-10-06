//
// Created by baronvladziu on 24.09.18.
//

#ifndef VULKAN_FDM_MATRIX_H
#define VULKAN_FDM_MATRIX_H

#include "header.h"
#include "ComplexFloat.h"


class Matrix {

    int _sizeX;
    int _sizeY;
    ComplexFloat ** _values;

public:
    Matrix(int x, int y);
    Matrix(const Matrix & m);
    int getX() const;
    int getY() const;
    ComplexFloat get(int x, int y) const;
    void set(int x, int y, ComplexFloat value);
    void fillWith(ComplexFloat value);
    Matrix extractUpper() const;
    Matrix extractDiagonal() const;
    Matrix extractLower() const;
    Matrix & operator=(const Matrix & m);
    Matrix operator+(const Matrix & m) const;
    Matrix operator-(const Matrix & m) const;
    Matrix operator*(const Matrix & m) const;
    Matrix operator*(ComplexFloat k) const;
    bool operator==(const Matrix & m) const;
    bool operator!=(const Matrix & m) const;
    Matrix extractDiagonalInverse() const;
    void removeZerosFromDiagonal();
    void solve();
    void print() const;
    void print(const std::string & filename) const;
    ~Matrix();

};


#endif //VULKAN_FDM_MATRIX_H
