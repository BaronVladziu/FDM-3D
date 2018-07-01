#pragma once
#include "header.h"

template <class T>
class Tab {
	const int _SIZE;
	T * _values = new T[_SIZE];

public:
	Tab(int size);
	int getSize() const;
	T & operator[](int i) const;
	~Tab();
};

template <class T>
Tab<T>::Tab(int size)
	: _SIZE(size)
{}

template <class T>
int Tab<T>::getSize() const {
	return _SIZE;
}

template <class T>
T & Tab<T>::operator[](int i) const {
	return _values[i];
}

template <class T>
Tab<T>::~Tab() {}