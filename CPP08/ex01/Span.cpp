#include "Span.hpp"


Span::Span(unsigned int n) : _n(n) {
    std::cout << "Span constructor called" << std::endl;
}

Span::Span(const Span &other) : _n(other._n), _numbers(other._numbers) {
    std::cout << "Span copy constructor called" << std::endl;
}

Span &Span::operator=(const Span &other) {
    std::cout << "Span assignment operator called" << std::endl;
    if (this != &other) {
        _n = other._n;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {
    std::cout << "Span destructor called" << std::endl;
}

void Span::addNumber(int number) {
    if (_numbers.size() >= _n) {
        throw std::out_of_range("Span is full");
    }
    _numbers.push_back(number);
}

void Span::addNumbers(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end) {
    if (std::distance(begin, end) > static_cast<int>(_n)) {
        throw std::out_of_range("Span is full");
    }
    _numbers.insert(_numbers.end(), begin, end);
}

unsigned int Span::shortestSpan()
{
    if (_numbers.size() < 2) {
        throw std::logic_error("Not enough numbers to find a span");
    }
    std::vector<unsigned int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());
    unsigned int minSpan = UINT_MAX;
    for (size_t i = 1; i < sorted.size(); ++i) {
        unsigned int span = sorted[i] - sorted[i - 1];
        if (span < minSpan) {
            minSpan = span;
        }
    }
    return minSpan;
}

unsigned int Span::longestSpan()
{
    if (_numbers.size() < 2) {
        throw std::logic_error("Not enough numbers to find a span");
    }
    unsigned int max = *std::max_element(_numbers.begin(), _numbers.end());
    unsigned int min = *std::min_element(_numbers.begin(), _numbers.end());
    return max - min;
}