#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <limits>

class ScalarConverter
{
    private:
        ScalarConverter();
        ~ScalarConverter();
        ScalarConverter(const ScalarConverter &src);
        ScalarConverter &operator=(const ScalarConverter &rhs);
    public:
        static void convert(const char *input);
};