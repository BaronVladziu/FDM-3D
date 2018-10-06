//
// Created by baronvladziu on 24.09.18.
//

#include "Matrix.h"


Matrix::Matrix(int x, int y)
    : _sizeX(x), _sizeY(y)
{
    _values = new ComplexFloat * [_sizeX];
    for (int i = 0; i < _sizeX; i++) {
        _values[i] = new ComplexFloat [_sizeY];
    }
}
Matrix::Matrix(const Matrix & m)
    : _sizeX(m.getX()), _sizeY(m.getY())
{
    _values = new ComplexFloat * [_sizeX];
    for (int i = 0; i < _sizeX; i++) {
        _values[i] = new ComplexFloat [_sizeY];
        for (int j = 0; j < _sizeY; j++) {
            _values[i][j] = m.get(i, j);
        }
    }
}
int Matrix::getX() const {
    return _sizeX;
}
int Matrix::getY() const {
    return _sizeY;
}
ComplexFloat Matrix::get(int x, int y) const {
    assert(x >= 0);
    assert(x < _sizeX);
    assert(y >= 0);
    assert(y < _sizeY);
    return _values[x][y];
}
void Matrix::set(int x, int y, ComplexFloat value) {
    assert(x >= 0);
    assert(x < _sizeX);
    assert(y >= 0);
    assert(y < _sizeY);
    _values[x][y] = value;
}
void Matrix::fillWith(ComplexFloat value) {
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            _values[i][j] = value;
        }
    }
}
Matrix Matrix::extractUpper() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract upper triangle of non-square matrix!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (int j = 0; j < _sizeY; j++) {
                if (i > j) {
                    result.set(i, j, _values[i][j]);
                } else {
                    result.set(i, j, ComplexFloat(0.f, 0.f));
                }
            }
        }
        return result;
    }
}
Matrix Matrix::extractDiagonal() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract diagonal of non-square matrix!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (int j = 0; j < _sizeY; j++) {
                if (i == j) {
                    result.set(i, j, _values[i][j]);
                } else {
                    result.set(i, j, ComplexFloat(0.f, 0.f));
                }
            }
        }
        return result;
    }
}
Matrix Matrix::extractLower() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract lower triangle of non-square matrix!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (int j = 0; j < _sizeY; j++) {
                if (i < j) {
                    result.set(i, j, _values[i][j]);
                } else {
                    result.set(i, j, ComplexFloat(0.f, 0.f));
                }
            }
        }
        return result;
    }
}
Matrix & Matrix::operator=(const Matrix & m) {
    _sizeX = m.getX();
    _sizeY = m.getY();
    _values = new ComplexFloat * [_sizeX];
    for (int i = 0; i < _sizeX; i++) {
        _values[i] = new ComplexFloat [_sizeY];
        for (int j = 0; j < _sizeY; j++) {
            _values[i][j] = m.get(i, j);
        }
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix & m) const {
    if (_sizeX != m.getX() || _sizeY != m.getY()) {
        std::cout << "ERROR: Tried to add matrices of different size!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (int j = 0; j < _sizeY; j++) {
                result.set(i, j, _values[i][j] + m.get(i, j));
            }
        }
        return result;
    }
}
Matrix Matrix::operator-(const Matrix & m) const {
    if (_sizeX != m.getX() || _sizeY != m.getY()) {
        std::cout << "ERROR: Tried to subtract matrices of different size!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (int j = 0; j < _sizeY; j++) {
                result.set(i, j, _values[i][j] - m.get(i, j));
            }
        }
        return result;
    }
}
Matrix Matrix::operator*(const Matrix & m) const {
    if (_sizeX != m.getY()) {
        std::cout << "ERROR: Tried to multiply matrices of wrong sizes!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(m.getX(), _sizeY);
        for (int i = 0; i < m.getX(); i++) {
            for (int j = 0; j < _sizeY; j++) {
                ComplexFloat v = ComplexFloat(0.f, 0.f);
                for (int k = 0; k < _sizeX; k++) {
                    v += _values[k][j]*m.get(i, k);
                }
                result.set(i, j, v);
            }
        }
        return result;
    }
}
Matrix Matrix::operator*(ComplexFloat k) const {
    Matrix result(_sizeX, _sizeY);
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            result.set(i, j, _values[i][j] * k);
        }
    }
    return result;
}
bool Matrix::operator==(const Matrix & m) const {
    if (m.getX() != _sizeX || m.getY() != _sizeY) {
        return false;
    }
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            if (_values[i][j] != m.get(i, j)) {
                return false;
            }
        }
    }
    return true;
}
bool Matrix::operator!=(const Matrix & m) const {
    return !operator==(m);
}
Matrix Matrix::extractDiagonalInverse() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract diagonal of non-square matrix!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (int j = 0; j < _sizeY; j++) {
                if (i == j) {
                    result.set(i, j, ComplexFloat(1.f, 0.f) / _values[i][j]);
                } else {
                    result.set(i, j, ComplexFloat(0.f, 0.f));
                }
            }
        }
        return result;
    }
}
void Matrix::removeZerosFromDiagonal() {
    for (int i = 0; i < getY(); i++) {
        if (get(i, i) == ComplexFloat(0.f, 0.f)) {
            //Find row with this variable
            int j = 0;
            while (get(i, j) == ComplexFloat(0.f, 0.f) and j < getY()) {
                j++;
            }
            if (j == getY()) {
                std::cout << "ERROR: Failed to remove all zeros from diagonal!" << std::endl;
            }
            //Add rows
            for (int k = 0; k < getX(); k++) {
                set(k, i, get(k, i) + get(k, j));
            }
        }
    }
}
void Matrix::solve() {
    //Gauss method ( O(n³) )
    for (int i = 0; i < _sizeY; i++) {
        //Scale row i
        for (int k = 0; k < _sizeX; k++) {
            _values[k][i] /= _values[i][i];
        }
        //Clear column
        for (int j = i+1; j < _sizeY; j++) {
            if (_values[i][j].real > 0.0001 || _values[i][j].imag > 0.0001) {
                //Scale row j
                std::cout << "Value: " << _values[i][j].toString() << std::endl;
                for (int k = 0; k < _sizeX; k++) {
                    _values[k][j] /= _values[i][j];
                    std::cout << _values[k][j].toString() << " , ";
                }
                std::cout << std::endl;
                //Subtract rows
                for (int k = 0; k < _sizeX; k++) {
                    _values[k][j] -= _values[k][i];
                }
            }
        }
    }
}
void Matrix::print() const {
    if (_sizeX == 1) {
        for (int j = 0; j < _sizeY; j++) {
            std::cout << _values[0][j].toString() << '\t';
        }
        std::cout << std::endl;
    } else {
        for (int j = 0; j < _sizeY; j++) {
            for (int i = 0; i < _sizeX; i++) {
                std::cout << _values[i][j].toString() << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
void Matrix::print(const std::string & filename) const {
    std::ofstream myfile;
    myfile.open (filename);
    if (_sizeX == 1) {
        for (int j = 0; j < _sizeY; j++) {
            myfile << _values[0][j].toString() << '\t';
        }
        myfile << std::endl;
    } else {
        for (int j = 0; j < _sizeY; j++) {
            for (int i = 0; i < _sizeX; i++) {
                myfile << _values[i][j].toString() << '\t';
            }
            myfile << std::endl;
        }
        myfile << std::endl;
    }
    myfile.close();
}
Matrix::~Matrix() {
    for (int i = 0; i < _sizeX; i++) {
        delete[] _values[i];
    }
    delete[] _values;
}
