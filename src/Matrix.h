//
// Created by baronvladziu on 24.09.18.
//

#ifndef VULKAN_FDM_MATRIX_H
#define VULKAN_FDM_MATRIX_H


#include "header.h"

template <class T>
class Matrix {

    int _sizeX = 0;
    int _sizeY = 0;
    T ** _values = nullptr;

public:
    Matrix(int x, int y);
    Matrix(const Matrix & m);
    int getX() const;
    int getY() const;
    T get(int x, int y) const;
    void set(int x, int y, const T & value);
    T getMax() const;
    void fillWithZeros();
    Matrix extractUpper() const;
    Matrix extractDiagonal() const;
    Matrix extractLower() const;
    Matrix & operator=(const Matrix & m);
    Matrix operator+(const Matrix & m) const;
    Matrix operator-(const Matrix & m) const;
    Matrix operator*(const Matrix & m) const;
    Matrix operator*(const T & k) const;
    void operator/=(float k);
    void operator/=(const T & k);
    bool operator==(const Matrix & m) const;
    bool operator!=(const Matrix & m) const;
    Matrix extractDiagonalInverse() const;
    void removeZerosFromDiagonal();
    void solve();
    void print() const;
    void print(const std::string & filename) const;
    ~Matrix();

private:
    void subtractX(int fromY, int posY, T factor);
    void scaleX(int posY, T factor);
    void cleanup();

};


#endif //VULKAN_FDM_MATRIX_H
