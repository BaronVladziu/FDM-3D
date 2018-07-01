#pragma once

template <class T>
class Tab {
	const unsigned int _SIZE;
	T * _values;

public:
	Tab(unsigned int size);
	unsigned int getSize() const;
	T & operator[](unsigned int i) const;
	~Tab();
};

template <class T>
Tab<T>::Tab(unsigned int size)
	: _SIZE(size)
{
	_values = new T[_SIZE];
}

template <class T>
unsigned int Tab<T>::getSize() const {
	return _SIZE;
}

template <class T>
T & Tab<T>::operator[](unsigned int i) const {
	return _values[i];
}

template <class T>
Tab<T>::~Tab() {
	delete[] _values;
}