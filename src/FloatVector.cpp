//
// Created by baronvladziu on 03.11.18.
//

#include "FloatVector.h"


FloatVector::FloatVector()
    : _size(0)
{
    fillWithZeros();
}
FloatVector::FloatVector(int size)
    : _size(size)
{
    fillWithZeros();
}
FloatVector::FloatVector(const FloatVector & v)
    : _size(v._size)
{
    fillWithZeros();
    for (auto pair : v._values) {
        _values.insert(pair);
    }
}
void FloatVector::resetSize(int size) {
    _size = size;
    fillWithZeros();
}
int FloatVector::getSize() const {
    return _size;
}
float FloatVector::get(int i) const {
    assert(i >= 0);
    assert(i < _size);
    auto result = _values.find(i);
    if (result != _values.end()) {
        return result->second;
    }
    return 0.f;
}
void FloatVector::set(int i, float value) {
    assert(i >= 0);
    assert(i < _size);
    if (value != 0.f) {
        _values[i] = value;
    }
}
float FloatVector::getMax() const {
    float result = 0.f;
    for (auto pair : _values) {
        if (pair.second > result) result = pair.second;
    }
    return result;
}
float FloatVector::getMaxAbs() const {
    float result = 0.f;
    for (auto pair : _values) {
        if (abs(pair.second) > result) result = abs(pair.second);
    }
    return result;
}
float FloatVector::getMin() const {
    float result = 0.f;
    for (auto pair : _values) {
        if (pair.second < result) result = pair.second;
    }
    return result;
}
float FloatVector::getSum() const {
    float result = 0.f;
    for (auto pair : _values) {
        result += pair.second;
    }
    return result;
}
float FloatVector::getAbsSum() const {
    float result = 0.f;
    for (auto pair : _values) {
        result += abs(pair.second);
    }
    return result;
}
float FloatVector::getNorm() const {
    float result = 0.f;
    for (auto pair : _values) {
        result += pair.second*pair.second;
    }
    return sqrt(result);
}
void FloatVector::fillWithZeros() {
    _values.clear();
}
void FloatVector::randomize(float maxValue) {
    for (int i = 0; i < _size; i++) {
        set(i, -maxValue + (((float) rand()) / (float) RAND_MAX)*(2*maxValue));
    }
}
void FloatVector::randomize(float minValue, float maxValue) {
    for (int i = 0; i < _size; i++) {
        set(i, minValue + (((float) rand()) / (float) RAND_MAX)*(maxValue - minValue));
    }
}
void FloatVector::randomize(int i, float minValue, float maxValue) {
    set(i, minValue + (((float) rand()) / (float) RAND_MAX)*(maxValue - minValue));
}
FloatVector & FloatVector::operator=(const FloatVector & v) {
    _size = v._size;
    fillWithZeros();
    for (auto pair : v._values) {
        _values.insert(pair);
    }
}
FloatVector FloatVector::operator+(const FloatVector & v) const {
    FloatVector result = *this;
    for (auto pair : v._values) {
        result.set(pair.first, result.get(pair.first) + pair.second);
    }
    return result;
}
FloatVector FloatVector::operator-(const FloatVector & v) const {
    FloatVector result = *this;
    for (auto pair : v._values) {
        result.set(pair.first, result.get(pair.first) - pair.second);
    }
    return result;
}
float FloatVector::operator*(const FloatVector & v) const {
    float result = 0.f;
    for (auto pair : v._values) {
        float k = get(pair.first);
        if (k != 0.f && pair.second != 0.f) {
            result += k * pair.second;
        }
    }
    return result;
}
FloatVector FloatVector::operator*(float k) const {
    FloatVector result(_size);
    for (auto pair : _values) {
        result.set(pair.first, pair.second * k);
    }
    return result;
}
FloatVector FloatVector::operator/(float k) const {
    FloatVector result(_size);
    for (auto pair : _values) {
        result.set(pair.first, pair.second / k);
    }
    return result;
}
void FloatVector::operator+=(const FloatVector & v) {
    for (auto pair : v._values) {
        set(pair.first, get(pair.first) + pair.second);
    }
}
void FloatVector::operator-=(const FloatVector & v) {
    for (auto pair : v._values) {
        set(pair.first, get(pair.first) - pair.second);
    }
}
void FloatVector::operator*=(float k) {
    for (auto pair : _values) {
        set(pair.first, get(pair.first) * k);
    }
}
void FloatVector::operator/=(float k) {
    for (auto pair : _values) {
        set(pair.first, get(pair.first) / k);
    }
}
bool FloatVector::operator==(const FloatVector & v) const {
    if (v._size != _size) return false;
    if (v._values.size() != _values.size()) return false;
    for (auto pair : _values) {
        if (pair.second != v.get(pair.first)) return false;
    }
    return true;
}
bool FloatVector::operator!=(const FloatVector & v) const {
    return !operator==(v);
}
void FloatVector::print() const {
    for (int j = 0; j < _size; j++) {
        std::cout << get(j) << '\t';
    }
    std::cout << std::endl;
}
void FloatVector::sparsePrint() const {
    for (auto value : _values) {
        std::cout << value.second << "*" << "x" << value.first << " + ";
    }
    std::cout << std::endl;
}
void FloatVector::print(const std::string & filename) const {
    std::ofstream myfile;
    myfile.open (filename);
    for (int j = 0; j < _size; j++) {
        std::cout << get(j) << '\t';
    }
    std::cout << std::endl;
    myfile.close();
}
