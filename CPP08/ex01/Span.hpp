#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <limits.h>


class Span {
private:
    unsigned int _n;
    std::vector<unsigned int> _numbers;
public:
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    void addNumber(int number);
    void addNumbers(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end);
    unsigned int shortestSpan();
    unsigned int longestSpan();
};




#endif