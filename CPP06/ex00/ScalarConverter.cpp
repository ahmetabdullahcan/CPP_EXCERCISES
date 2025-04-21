#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
    std::cout << "ScalarConverter default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &src) {
    *this = src;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs){
    (void)rhs;
    return *this;
}

ScalarConverter::~ScalarConverter() {
    std::cout << "ScalarConverter destructor called" << std::endl;
}

static bool checkValidInput(const std::string &input) {
    if (input.empty()) {
        return false;
    }
    if (input == "-inf" || input == "+inf" || input == "inf") {
        return true;
    }
    if (input == "-inff" || input == "+inff" || input == "inff") {
        return true;
    }
    if (input.length() == 1 && (input[0] > 31 && input[0] < 127)) {
        return true;
    }

    int dotCount = 0;
    int signCount = 0;
    int fCount = 0;
    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '.') {
            dotCount++;
        } else if (input[i] == 'f') {
            fCount++;
        } else if (input[i] == '-' || input[i] == '+') {
            signCount++;
        } else if (!std::isdigit(input[i])) {
            return false;
        }
    }
    if (dotCount > 1 || signCount > 1 || fCount > 1) {
        return false;
    }
    if (dotCount == 0 && fCount == 1) {
        return false;
    }
    return true;
}


static int convertToInt(const std::string &input) {
    std::string newInput = input;
    if (input.find(".") != std::string::npos)
        newInput = input.substr(0, input.find("."));
    if (newInput.length() == 1 && (newInput[0] > 31 && newInput[0] < 127)) {
        if (newInput[0] >='0' && newInput[0] <= '9') {
            return static_cast<int>(newInput[0] - '0');
        }
        return static_cast<int>(newInput[0]);
    }
    std::stringstream ss(newInput);
    int value;
    ss >> value;
    if (ss.fail() || !ss.eof()) {
        throw std::invalid_argument("Invalid input for int conversion");
    }
    return value;
}


static char convertToChar(const std::string &input) {
    if (input.length() == 1 && (input[0] > 31 && input[0] < 127)) {
        if (input[0] >='0' && input[0] <= '9') {
            return static_cast<char>(input[0] - '0');
        }
        return input[0];
    }
    std::string newInput = input;
    if (input.find(".") != std::string::npos)
        newInput = input.substr(0, input.find("."));
    if (newInput.find("f") != std::string::npos)
        newInput = newInput.substr(0, newInput.find("f"));
    if (newInput.find("F") != std::string::npos)
        newInput = newInput.substr(0, newInput.find("F"));
    if (newInput.length() == 1 && (newInput[0] > 31 && newInput[0] < 127)) {
        if (newInput[0] >='0' && newInput[0] <= '9') {
            return static_cast<char>(newInput[0] - '0');
        }
        return newInput[0];
    }
    std::stringstream ss(newInput);
    int value;
    ss >> value;
    if (ss.fail() || !ss.eof()) {
        throw std::invalid_argument("Invalid input for char conversion");
    }
    if (value < 0 || value > 255) {
        throw std::out_of_range("Value out of range for char conversion");
    }
    return static_cast<char>(value);
}
static float convertToFloat(const std::string &input) {
    std::string newInput = input;

    size_t pos = newInput.find('f');
    if (pos != std::string::npos && newInput.length() > 1)
        newInput = newInput.substr(0, pos);
    
    if (newInput.length() == 1 && (newInput[0] > 31 && newInput[0] < 127)) {
        if (newInput[0] >= '0' && newInput[0] <= '9') {
            return static_cast<float>(newInput[0] - '0');
        }
        return static_cast<float>(newInput[0]);
    }

    std::stringstream ss(newInput);
    float value;
    ss >> value;
    if (ss.fail() || !ss.eof()) {
        throw std::invalid_argument("Invalid input for float conversion");
    }
    if (value < -3.402823466e+38f || value > 3.402823466e+38f) {
        throw std::out_of_range("Value out of range for float conversion");
    }
    return value;
}
static double convertToDouble(const std::string &input) {
    std::string newInput = input;
    size_t pos = newInput.find('f');
    if (pos != std::string::npos && newInput.length() > 1)
        newInput = newInput.substr(0, pos);
    if (newInput.length() == 1 && (newInput[0] > 31 && newInput[0] < 127)) {
        if (newInput[0] >='0' && newInput[0] <= '9') {
            return static_cast<float>(newInput[0] - '0');
        }
        return static_cast<float>(newInput[0]);
    }
    std::stringstream ss(newInput);
    double value;
    ss >> value;
    if (ss.fail() || !ss.eof()) {
        throw std::invalid_argument("Invalid input for double conversion");
    }
    if (value < -1.7976931348623157e+308 || value > 1.7976931348623157e+308) {
        throw std::out_of_range("Value out of range for double conversion");
    }
    return value;
}


void ScalarConverter::convert(const char *input) {
    std::string rawStr(input);

    if (rawStr == "-inf" || rawStr == "+inf" || rawStr == "inf") {
        std::cout << "char : impossible" << std::endl;
        std::cout << "int : impossible" << std::endl;
        std::cout << "float : " << rawStr << "f" << std::endl;
        std::cout << "double : " << rawStr << std::endl;
        return;
    }
    if (rawStr == "-inff" || rawStr == "+inff" || rawStr == "inff") {
        std::cout << "char : impossible" << std::endl;
        std::cout << "int : impossible" << std::endl;
        std::cout << "float : " << rawStr << std::endl;
        std::cout << "double : " << rawStr.substr(0, rawStr.length() - 1) << std::endl;
        return;
    }

    if (!checkValidInput(rawStr)) {
        std::cout << "char : impossible" << std::endl;
        std::cout << "int : impossible" << std::endl;
        std::cout << "float : nanf" << std::endl;
        std::cout << "double : nan" << std::endl;
        return;
    }

    try {
        char c = convertToChar(rawStr);
        if (c >= 32 && c <= 126)
            std::cout << "char : '" << c << "'" << std::endl;
        else
            std::cout << "char : Non displayable" << std::endl;
    } catch (...) {
        std::cout << "char : impossible" << std::endl;
    }

    try {
        int i = convertToInt(rawStr);
        std::cout << "int : " << i << std::endl;
    } catch (...) {
        std::cout << "int : impossible" << std::endl;
    }

    // Convert and print float
    try {
        float f = convertToFloat(rawStr);
        std::cout << "float : " << f;
        if (f == static_cast<int>(f) && rawStr.find('.') == std::string::npos)
            std::cout << ".0";
        std::cout << "f" << std::endl;
    } catch (...) {
        std::cout << "float : impossible" << std::endl;
    }

    try {
        double d = convertToDouble(rawStr);
        std::cout << "double : " << d;
        if (d == static_cast<int>(d) && rawStr.find('.') == std::string::npos)
            std::cout << ".0";
        std::cout << std::endl;
    } catch (...) {
        std::cout << "double : impossible" << std::endl;
    }
}
