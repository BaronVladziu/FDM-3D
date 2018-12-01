//
// Created by baronvladziu on 24.09.18.
//

#include "Matrix.h"
#include "ComplexFloat.h"

template <class T>
Matrix<T>::Matrix(int x, int y)
    : _sizeX(x), _sizeY(y)
{
    if (_values != nullptr) {
        cleanup();
    }
    _values = new T * [_sizeX];
    for (int i = 0; i < _sizeX; i++) {
        _values[i] = new T [_sizeY];
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix & m)
    : _sizeX(m.getX()), _sizeY(m.getY())
{
    if (_values != nullptr) {
        cleanup();
    }
    _values = new T * [_sizeX];
    for (int i = 0; i < _sizeX; i++) {
        _values[i] = new T [_sizeY];
        for (int j = 0; j < _sizeY; j++) {
            _values[i][j] = m.get(i, j);
        }
    }
}

template <class T>
int Matrix<T>::getX() const {
    return _sizeX;
}

template <class T>
int Matrix<T>::getY() const {
    return _sizeY;
}

template <class T>
T Matrix<T>::get(int x, int y) const {
    assert(x >= 0);
    assert(x < _sizeX);
    assert(y >= 0);
    assert(y < _sizeY);
    return _values[x][y];
}

template <class T>
void Matrix<T>::set(int x, int y, const T & value) {
    assert(x >= 0);
    assert(x < _sizeX);
    assert(y >= 0);
    assert(y < _sizeY);
    _values[x][y] = value;
}

template <>
ComplexFloat Matrix<ComplexFloat>::getMax() const {
    ComplexFloat result = get(0, 0);
    float resultAbs = result.abs();
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            ComplexFloat cand = get(i, j);
            float candAbs = cand.abs();
            if (candAbs > resultAbs) {
                result = cand;
                resultAbs = candAbs;
            }
        }
    }
    return result;
}

template <class T>
T Matrix<T>::getMax() const {
    T result = get(0, 0);
    float resultAbs = abs(result);
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            T cand = get(i, j);
            float candAbs = abs(cand);
            if (candAbs > resultAbs) {
                result = cand;
                resultAbs = candAbs;
            }
        }
    }
    return result;
}

template <class T>
void Matrix<T>::fillWithZeros() {
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            _values[i][j] = T(0.f);
        }
    }
}

template <class T>
Matrix<T> Matrix<T>::extractUpper() const {
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
                    result.set(i, j, T(0.f));
                }
            }
        }
        return result;
    }
}

template <class T>
Matrix<T> Matrix<T>::extractDiagonal() const {
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
                    result.set(i, j, T(0.f));
                }
            }
        }
        return result;
    }
}

template <class T>
Matrix<T> Matrix<T>::extractLower() const {
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
                    result.set(i, j, T(0.f));
                }
            }
        }
        return result;
    }
}

template <class T>
Matrix<T> & Matrix<T>::operator=(const Matrix & m) {
    _sizeX = m.getX();
    _sizeY = m.getY();
    if (_values != nullptr) {
        cleanup();
    }
    _values = new T * [_sizeX];
    for (int i = 0; i < _sizeX; i++) {
        _values[i] = new T [_sizeY];
        for (int j = 0; j < _sizeY; j++) {
            _values[i][j] = m.get(i, j);
        }
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix & m) const {
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

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix & m) const {
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

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix & m) const {
    if (_sizeX != m.getY()) {
        std::cout << "ERROR: Tried to multiply matrices of wrong sizes!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(m.getX(), _sizeY);
        for (int i = 0; i < m.getX(); i++) {
            for (int j = 0; j < _sizeY; j++) {
                T v = T(0.f);
                for (int k = 0; k < _sizeX; k++) {
                    v += _values[k][j]*m.get(i, k);
                }
                result.set(i, j, v);
            }
        }
        return result;
    }
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T & k) const {
    Matrix result(_sizeX, _sizeY);
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            result.set(i, j, _values[i][j] * k);
        }
    }
    return result;
}

template <class T>
void Matrix<T>::operator/=(float k) {
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            _values[i][j] /= k;
        }
    }
}

template <class T>
void Matrix<T>::operator/=(const T & k) {
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            _values[i][j] /= k;
        }
    }
}

template <class T>
bool Matrix<T>::operator==(const Matrix & m) const {
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

template <class T>
bool Matrix<T>::operator!=(const Matrix & m) const {
    return !operator==(m);
}

template <class T>
Matrix<T> Matrix<T>::extractDiagonalInverse() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract diagonal of non-square matrix!" << std::endl;
        return Matrix(0, 0);
    } else {
        Matrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (int j = 0; j < _sizeY; j++) {
                if (i == j) {
                    result.set(i, j, T(1.f) / _values[i][j]);
                } else {
                    result.set(i, j, T(0.f));
                }
            }
        }
        return result;
    }
}

template <class T>
void Matrix<T>::removeZerosFromDiagonal() {
    for (int i = 0; i < getY(); i++) {
        if (get(i, i) == T(0.f)) {
            //Find row with this variable
            int j = 0;
            while (get(i, j) == T(0.f) and j < getY()) {
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

template <class T>
void Matrix<T>::solve() {
//    //Gauss method ( O(n³) )
//    for (int i = 0; i < _sizeY; i++) {
//        //Scale row i
//        for (int k = 0; k < _sizeX; k++) {
//            _values[k][i] /= _values[i][i];
//        }
//        //Clear column
//        for (int j = i+1; j < _sizeY; j++) {
//            if (_values[i][j] != 0) {
//                //Scale row j
////                std::cout << "Value: " << _values[i][j].toString() << std::endl;
//                for (int k = 0; k < _sizeX; k++) {
//                    _values[k][j] /= _values[i][j];
////                    std::cout << _values[k][j].toString() << " , ";
//                }
////                std::cout << std::endl;
//                //Subtract rows
//                for (int k = 0; k < _sizeX; k++) {
//                    _values[k][j] -= _values[k][i];
//                }
//            }
//        }
//    }

    assert(_sizeX == _sizeY + 1);
    for (int j = 0; j < _sizeY; j++) {
        if (_values[j][j] != 0) {
            scaleX(j, _values[j][j]);
            for (int i = j + 1; i < _sizeY; i++) {
                subtractX(i, j, _values[j][i]);
            }
        } else {
            std::cout << "Failed to solve matrix properly!" << std::endl;
            return;
        }
    }
    for (int j = _sizeY - 1; j >= 0; j--) {
        if (_values[j][j] != 0) {
            scaleX(j, _values[j][j]);
            for (int i = j - 1; i >= 0; i--) {
                subtractX(i, j, _values[j][i]);
            }
        }
    }
}

template <>
void Matrix<ComplexFloat>::print() const {
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

template <class T>
void Matrix<T>::print() const {
    if (_sizeX == 1) {
        for (int j = 0; j < _sizeY; j++) {
            std::cout << _values[0][j] << '\t';
        }
        std::cout << std::endl;
    } else {
        for (int j = 0; j < _sizeY; j++) {
            for (int i = 0; i < _sizeX; i++) {
                std::cout << _values[i][j] << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}


template <>
void Matrix<ComplexFloat>::print(const std::string & filename) const {
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

template <class T>
void Matrix<T>::print(const std::string & filename) const {
    std::ofstream myfile;
    myfile.open (filename);
    if (_sizeX == 1) {
        for (int j = 0; j < _sizeY; j++) {
            myfile << _values[0][j] << '\t';
        }
        myfile << std::endl;
    } else {
        for (int j = 0; j < _sizeY; j++) {
            for (int i = 0; i < _sizeX; i++) {
                myfile << _values[i][j] << '\t';
            }
            myfile << std::endl;
        }
        myfile << std::endl;
    }
    myfile.close();
}

template <class T>
Matrix<T>::~Matrix() {
    cleanup();
}

template <class T>
void Matrix<T>::subtractX(int fromY, int posY, T factor) {
    if (factor != 0) {
        for (int i = 0; i < _sizeX; i++) {
            _values[i][fromY] -= factor * _values[i][posY];
        }
    }
}

template <class T>
void Matrix<T>::scaleX(int posY, T factor) {
    if (factor != 0) {
        for (int i = 0; i < _sizeX; i++) {
            _values[i][posY] /= factor;
        }
    }
}

template <class T>
void Matrix<T>::cleanup() {
    if (_values != nullptr) {
        for (int i = 0; i < _sizeX; i++) {
            delete[] _values[i];
        }
        delete[] _values;
    }
}


template class Matrix<float>;
template class Matrix<double>;
template class Matrix<ComplexFloat>;