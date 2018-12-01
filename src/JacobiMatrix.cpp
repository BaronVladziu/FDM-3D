//
// Created by baronvladziu on 30.11.18.
//

#include "JacobiMatrix.h"

JacobiMatrix::JacobiMatrix(int x, int y)
        : _sizeX(x), _sizeY(y)
{
    fillWithZeros();
}
JacobiMatrix::JacobiMatrix(const JacobiMatrix & m)
        : _sizeX(m.getX()), _sizeY(m.getY())
{
    fillWithZeros();
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, float> & v : m.getValues(i)) {
            _values[i].insert(v);
        }
    }
}
int JacobiMatrix::getX() const {
    return _sizeX;
}
int JacobiMatrix::getY() const {
    return _sizeY;
}
float JacobiMatrix::get(int x, int y) const {
    assert(x >= 0);
    assert(x < _sizeX);
    assert(y >= 0);
    assert(y < _sizeY);
    auto result = _values[y].find(x);
    if (result != _values[y].end()) {
        return (*result).second;
    }
    return 0.f;
}
const std::unordered_map<int, float> & JacobiMatrix::getValues(int y) const {
    return _values[y];
}
void JacobiMatrix::set(int x, int y, float value) {
    assert(x >= 0);
    assert(x < _sizeX);
    assert(y >= 0);
    assert(y < _sizeY);
    if (value != 0.f) {
        _values[y][x] = value;
    }
}
float JacobiMatrix::getMax() const {
    float result = get(0, 0);
    float resultAbs = abs(result);
    for (int j = 0; j < _sizeY; j++) {
        for (const std::pair<const int, float> & v : _values[j]) {
            float cand = v.second;
            float candAbs = abs(cand);
            if (candAbs > resultAbs) {
                result = cand;
                resultAbs = candAbs;
            }
        }
    }
    return result;
}
void JacobiMatrix::fillWithZeros() {
    if (_values != nullptr) {
        cleanup();
    }
    _values = new std::unordered_map<int, float> [_sizeY];
}
void JacobiMatrix::randomize() {
    if (_values != nullptr) {
        cleanup();
    }
    _values = new std::unordered_map<int, float> [_sizeY];
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            set(i, j, -1 + (((float) rand()) / (float) RAND_MAX)*2);
        }
    }
}
JacobiMatrix JacobiMatrix::extractUpper() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract upper triangle of non-square matrix!" << std::endl;
        return JacobiMatrix(0, 0);
    } else {
        JacobiMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, float> & v : _values[i]) {
                if (i > v.first) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
JacobiMatrix JacobiMatrix::extractDiagonal() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract diagonal of non-square matrix!" << std::endl;
        return JacobiMatrix(0, 0);
    } else {
        JacobiMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, float> & v : _values[i]) {
                if (i == v.first) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
JacobiMatrix JacobiMatrix::extractLower() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract lower triangle of non-square matrix!" << std::endl;
        return JacobiMatrix(0, 0);
    } else {
        JacobiMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, float> & v : _values[i]) {
                if (i < v.first) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
JacobiMatrix & JacobiMatrix::operator=(const JacobiMatrix & m) {
    _sizeX = m.getX();
    _sizeY = m.getY();
    fillWithZeros();
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, float> & v : m.getValues(i)) {
            _values[i].insert(v);
        }
    }
    return *this;
}
JacobiMatrix JacobiMatrix::operator+(const JacobiMatrix & m) const {
    if (_sizeX != m.getX() || _sizeY != m.getY()) {
        std::cout << "ERROR: Tried to add matrices of different size!" << std::endl;
        return JacobiMatrix(0, 0);
    } else {
        JacobiMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, float> & v : _values[i]) {
                float v2 = m.get(v.first, i);
                result.set(v.first, i, v.second + v2);
            }
            for (const std::pair<const int, float> & v : m.getValues(i)) {
                auto v2 = _values[i].find(v.first);
                if (v2 == _values[i].end()) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
JacobiMatrix JacobiMatrix::operator-(const JacobiMatrix & m) const {
    if (_sizeX != m.getX() || _sizeY != m.getY()) {
        std::cout << "ERROR: Tried to subtract matrices of different size!" << std::endl;
        return JacobiMatrix(0, 0);
    } else {
        JacobiMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, float> & v : _values[i]) {
                float v2 = m.get(v.first, i);
                result.set(v.first, i, v.second - v2);
            }
            for (const std::pair<const int, float> & v : m.getValues(i)) {
                auto v2 = _values[i].find(v.first);
                if (v2 == _values[i].end()) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
JacobiMatrix JacobiMatrix::operator*(const JacobiMatrix & m) const {
    if (_sizeX != m.getY()) {
        std::cout << "ERROR: Tried to multiply matrices of wrong sizes!" << std::endl;
        return JacobiMatrix(0, 0);
    } else {
        //"Transpose" m with O(n)
        JacobiMatrix tm(_sizeY, _sizeX);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, float> & v : _values[i]) {
                tm.set(i, v.first, v.second);
            }
        }
        //Multiply with O(n) <3
        JacobiMatrix result(m.getX(), _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (const std::pair<const int, float> & v : tm.getValues(i)) {
                for (const std::pair<const int, float> & v2 : m.getValues(i)) {
                    result.set(v2.first, v.first, result.get(v2.first, v.first) + v2.second*v.second);
                }
            }
        }
        return result;
    }
}
JacobiMatrix JacobiMatrix::operator*(float k) const {
    JacobiMatrix result(_sizeX, _sizeY);
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, float> & v : _values[i]) {
            result.set(v.first, i, v.second * k);
        }
    }
    return result;
}
void JacobiMatrix::operator/=(float k) {
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, float> & v : _values[i]) {
            set(v.first, i, v.second / k);
        }
    }
}
bool JacobiMatrix::operator==(const JacobiMatrix & m) const {
    if (m.getX() != _sizeX || m.getY() != _sizeY) {
        return false;
    }
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, float> & v : _values[i]) {
            if (v.second != m.get(v.first, i)) {
                return false;
            }
        }
    }
    return true;
}
bool JacobiMatrix::operator!=(const JacobiMatrix & m) const {
    return !operator==(m);
}
JacobiMatrix JacobiMatrix::extractDiagonalInverse() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract diagonal of non-square matrix!" << std::endl;
        return JacobiMatrix(0, 0);
    } else {
        JacobiMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            result.set(i, i, 1.f / get(i, i));
        }
        return result;
    }
}
void JacobiMatrix::print() const {
    if (_sizeX == 1) {
        for (int j = 0; j < _sizeY; j++) {
            if (get(0, j) != 0.f) {
                std::cout << "(" << get(0, j) << ")*x_" << j << " + ";
            }
        }
        std::cout << std::endl;
    } else {
        for (int j = 0; j < _sizeY; j++) {
            for (const std::pair<const int, float> & v : _values[j]) {
                std::cout << v.second << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
void JacobiMatrix::print(const std::string & filename) const {
    std::ofstream myfile;
    myfile.open (filename);
    if (_sizeX == 1) {
        for (int j = 0; j < _sizeY; j++) {
            myfile << get(0,j) << '\t';
        }
        myfile << std::endl;
    } else {
        for (int j = 0; j < _sizeY; j++) {
            for (const std::pair<const int, float> & v : _values[j]) {
                myfile << v.second << '\t';
            }
            myfile << std::endl;
        }
        myfile << std::endl;
    }
    myfile.close();
}
JacobiMatrix::~JacobiMatrix() {
    cleanup();
}

void JacobiMatrix::cleanup() {
    if (_values != nullptr) {
        delete[] _values;
    }
}