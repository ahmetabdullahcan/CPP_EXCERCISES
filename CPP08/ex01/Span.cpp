#include "Span.hpp"

Span::Span(unsigned int n) : _maxSize(n) {}
Span::Span(const Span& other) : _maxSize(other._maxSize), _v(other._v) {}
Span& Span::operator=(const Span& other) {
    if (this != &other) {
        _maxSize = other._maxSize;
        _v = other._v;
    }
    return *this;
}
Span::~Span() {}
void Span::addNumber(int number) {
    if (_v.size() >= _maxSize) {
        throw std::out_of_range("Span is full");
    }
    _v.push_back(number);
}
void Span::addNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    if (std::distance(begin, end) + _v.size() > _maxSize) {
        throw std::out_of_range("Span is full");
    }
    _v.insert(_v.end(), begin, end);
}
unsigned int Span::longestSpan() const {
    if (_v.size() < 2) {
        throw std::logic_error("Not enough elements to find a span");
    }
    std::vector <int> tmp = _v;
    std::sort(tmp.begin(), tmp.end());
    return static_cast<unsigned int>(tmp.back() - tmp.front());
}

unsigned int Span::shortestSpan() const {
    if (_v.size() < 2) {
        throw std::logic_error("Not enough elements to find a span");
    }
    std::vector <int> tmp = _v;
    std::sort(tmp.begin(), tmp.end());
    unsigned int minSpan = std::numeric_limits<unsigned int>::max();
    for (size_t i = 1; i < tmp.size(); ++i) {
        unsigned int span = static_cast<unsigned int>(tmp[i] - tmp[i - 1]);
        if (span < minSpan) {
            minSpan = span;
        }
    }
    return minSpan;
}