#pragma once

#include <iostream>

template <typename T>

class Array {
private:
    T* _array;
    unsigned int _size;
public:

    Array(): _array(nullptr), _size(0) {
        std::cout << "Default constructor called" << std::endl;
    }
    Array(unsigned int n): _array(new T[n]), _size(n) {
        std::cout << "Constructor with size called" << std::endl;
    }
    Array(const Array& other): _array(new T[other._size]), _size(other._size) {
        std::cout << "Copy constructor called" << std::endl;
        for (unsigned int i = 0; i < _size; ++i) {
            _array[i] = other._array[i];
        }
    }
    Array& operator=(const Array& other) {
        std::cout << "Copy assignment operator called" << std::endl;
        if (this != &other) {
            delete[] _array;
            _size = other._size;
            _array = new T[_size];
            for (unsigned int i = 0; i < _size; ++i) {
                _array[i] = other._array[i];
            }
        }
        return *this;
    }
    ~Array() {
        std::cout << "Destructor called" << std::endl;
        delete[] _array;
    }
    unsigned int size() const {
        return _size;
    }
    T& operator[](unsigned int index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _array[index];
    }
};