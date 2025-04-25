#include "Span.hpp"

int main(void)
{
    Span sp = Span(10000);
    srand(time(NULL));

    for (int i = 0; i < 10000; ++i) {
        sp.addNumber(rand() % 100000);
    }
    try {
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        sp.addNumber(10000);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}