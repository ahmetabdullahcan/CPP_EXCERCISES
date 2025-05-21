#include "Span.hpp"


int main()
{

    {
        std::cout << "========================" << std::endl;
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << "Finding shortest and longest span in 5 elements span" << std::endl;
        std::cout << "Shortest span : " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp.longestSpan() << std::endl;
    }
    {
        std::cout << "========================" << std::endl;
        Span sp = Span(100000);
        std::vector<unsigned int> numbers(100000);
        for (unsigned int i = 0; i < 100000; ++i) {
            numbers[i] = i;
        }
        sp.addNumbers(numbers.begin(), numbers.end());
        std::cout << "Finding shortest and longest span in 100000 elements span" << std::endl;
        std::cout << "Shortest span : " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp.longestSpan() << std::endl;
    }
    {
        std::cout << "========================" << std::endl;
        Span sp = Span(5);
        std::cout << "Trying to add more than 5 elements to a span of size 5" << std::endl;
        try {
            sp.addNumber(1);
            sp.addNumber(2);
            sp.addNumber(3);
            sp.addNumber(4);
            sp.addNumber(5);
            sp.addNumber(6);
        } catch (const std::out_of_range &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    {
        std::cout << "========================" << std::endl;
        Span sp = Span(5);
        std::cout << "Trying to find shortest span in an empty span" << std::endl;
        try {
            std::cout << sp.shortestSpan() << std::endl;
        } catch (const std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    {
        std::cout << "========================" << std::endl;
        std::cout << "Trying to find longest span in an empty span" << std::endl;
        Span sp = Span(5);
        try {
            std::cout << sp.longestSpan() << std::endl;
        } catch (const std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    std::cout << "========================" << std::endl;
    return 0;
}