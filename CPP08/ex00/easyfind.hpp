#pragma once

#include <algorithm>
#include <exception>

class NotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Element not found";
    }
};

template <typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end()) {
        throw NotFoundException();
    }
    return it;
}

