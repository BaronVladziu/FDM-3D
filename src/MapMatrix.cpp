//
// Created by baronvladziu on 26.10.18.
//

#include "MapMatrix.h"


MapMatrix::MapMatrix(int x, int y)
        : _sizeX(x), _sizeY(y)
{
    fillWithZeros();
}
MapMatrix::MapMatrix(const MapMatrix & m)
        : _sizeX(m.getX()), _sizeY(m.getY())
{
    fillWithZeros();
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, ComplexFloat> & v : m.getValues(i)) {
            _values[i].insert(v);
        }
    }
}
int MapMatrix::getX() const {
    return _sizeX;
}
int MapMatrix::getY() const {
    return _sizeY;
}
ComplexFloat MapMatrix::get(int x, int y) const {
    assert(x >= 0);
    assert(x < _sizeX);
    assert(y >= 0);
    assert(y < _sizeY);
    auto result = _values[y].find(x);
    if (result != _values[y].end()) {
        return (*result).second;
    }
    return ComplexFloat(0,0);
}
const std::unordered_map<int, ComplexFloat> & MapMatrix::getValues(int y) const {
    return _values[y];
}
void MapMatrix::set(int x, int y, const ComplexFloat & value) {
    assert(x >= 0);
    assert(x < _sizeX);
    assert(y >= 0);
    assert(y < _sizeY);
    if (value != ComplexFloat(0,0)) {
        _values[y][x] = value;
    }
}
ComplexFloat MapMatrix::getMax() const {
    ComplexFloat result = get(0, 0);
    float resultAbs = result.abs();
    for (int j = 0; j < _sizeY; j++) {
        for (const std::pair<const int, ComplexFloat> & v : _values[j]) {
            ComplexFloat cand = v.second;
            float candAbs = cand.abs();
            if (candAbs > resultAbs) {
                result = cand;
                resultAbs = candAbs;
            }
        }
    }
    return result;
}
void MapMatrix::fillWithZeros() {
    if (_values != nullptr) {
        cleanup();
    }
    _values = new std::unordered_map<int, ComplexFloat> [_sizeY];
}
MapMatrix MapMatrix::extractUpper() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract upper triangle of non-square matrix!" << std::endl;
        return MapMatrix(0, 0);
    } else {
        MapMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
                if (i > v.first) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
MapMatrix MapMatrix::extractDiagonal() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract diagonal of non-square matrix!" << std::endl;
        return MapMatrix(0, 0);
    } else {
        MapMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
                if (i == v.first) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
MapMatrix MapMatrix::extractLower() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract lower triangle of non-square matrix!" << std::endl;
        return MapMatrix(0, 0);
    } else {
        MapMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
                if (i < v.first) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
MapMatrix & MapMatrix::operator=(const MapMatrix & m) {
    _sizeX = m.getX();
    _sizeY = m.getY();
    fillWithZeros();
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, ComplexFloat> & v : m.getValues(i)) {
            _values[i].insert(v);
        }
    }
    return *this;
}
MapMatrix MapMatrix::operator+(const MapMatrix & m) const {
    if (_sizeX != m.getX() || _sizeY != m.getY()) {
        std::cout << "ERROR: Tried to add matrices of different size!" << std::endl;
        return MapMatrix(0, 0);
    } else {
        MapMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
                ComplexFloat v2 = m.get(v.first, i);
                result.set(v.first, i, v.second + v2);
            }
            for (const std::pair<const int, ComplexFloat> & v : m.getValues(i)) {
                auto v2 = _values[i].find(v.first);
                if (v2 == _values[i].end()) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
MapMatrix MapMatrix::operator-(const MapMatrix & m) const {
    if (_sizeX != m.getX() || _sizeY != m.getY()) {
        std::cout << "ERROR: Tried to subtract matrices of different size!" << std::endl;
        return MapMatrix(0, 0);
    } else {
        MapMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
                ComplexFloat v2 = m.get(v.first, i);
                result.set(v.first, i, v.second - v2);
            }
            for (const std::pair<const int, ComplexFloat> & v : m.getValues(i)) {
                auto v2 = _values[i].find(v.first);
                if (v2 == _values[i].end()) {
                    result.set(v.first, i, v.second);
                }
            }
        }
        return result;
    }
}
MapMatrix MapMatrix::operator*(const MapMatrix & m) const {
    if (_sizeX != m.getY()) {
        std::cout << "ERROR: Tried to multiply matrices of wrong sizes!" << std::endl;
        return MapMatrix(0, 0);
    } else {
        //"Transpose" m with O(n)
        MapMatrix tm(_sizeY, _sizeX);
        for (int i = 0; i < _sizeY; i++) {
            for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
                tm.set(i, v.first, v.second);
            }
        }
        //Multiply with O(n) <3
        MapMatrix result(m.getX(), _sizeY);
        for (int i = 0; i < _sizeX; i++) {
            for (const std::pair<const int, ComplexFloat> & v : tm.getValues(i)) {
                for (const std::pair<const int, ComplexFloat> & v2 : m.getValues(i)) {
                    result.set(v2.first, v.first, result.get(v2.first, v.first) + v2.second*v.second);
                }
            }
        }
        return result;
    }
}
MapMatrix MapMatrix::operator*(const ComplexFloat & k) const {
    MapMatrix result(_sizeX, _sizeY);
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
            result.set(v.first, i, v.second * k);
        }
    }
    return result;
}
void MapMatrix::operator/=(float k) {
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
            set(v.first, i, v.second / k);
        }
    }
}
void MapMatrix::operator/=(const ComplexFloat & k) {
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
            set(v.first, i, v.second / k);
        }
    }
}
bool MapMatrix::operator==(const MapMatrix & m) const {
    if (m.getX() != _sizeX || m.getY() != _sizeY) {
        return false;
    }
    for (int i = 0; i < _sizeY; i++) {
        for (const std::pair<const int, ComplexFloat> & v : _values[i]) {
            if (v.second != m.get(v.first, i)) {
                return false;
            }
        }
    }
    return true;
}
bool MapMatrix::operator!=(const MapMatrix & m) const {
    return !operator==(m);
}
MapMatrix MapMatrix::extractDiagonalInverse() const {
    if (_sizeX != _sizeY) {
        std::cout << "ERROR: Tried to extract diagonal of non-square matrix!" << std::endl;
        return MapMatrix(0, 0);
    } else {
        MapMatrix result(_sizeX, _sizeY);
        for (int i = 0; i < _sizeY; i++) {
            result.set(i, i, ComplexFloat(1.f, 0.f) / get(i, i));
        }
        return result;
    }
}
void MapMatrix::print() const {
    if (_sizeX == 1) {
        for (int j = 0; j < _sizeY; j++) {
            std::cout << get(0,j).toString() << '\t';
        }
        std::cout << std::endl;
    } else {
        for (int j = 0; j < _sizeY; j++) {
            for (const std::pair<const int, ComplexFloat> & v : _values[j]) {
                std::cout << v.second.toString() << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
void MapMatrix::print(const std::string & filename) const {
    std::ofstream myfile;
    myfile.open (filename);
    if (_sizeX == 1) {
        for (int j = 0; j < _sizeY; j++) {
            myfile << get(0,j).toString() << '\t';
        }
        myfile << std::endl;
    } else {
        for (int j = 0; j < _sizeY; j++) {
            for (const std::pair<const int, ComplexFloat> & v : _values[j]) {
                myfile << v.second.toString() << '\t';
            }
            myfile << std::endl;
        }
        myfile << std::endl;
    }
    myfile.close();
}
MapMatrix::~MapMatrix() {
    cleanup();
}

void MapMatrix::cleanup() {
    if (_values != nullptr) {
        delete[] _values;
    }
}