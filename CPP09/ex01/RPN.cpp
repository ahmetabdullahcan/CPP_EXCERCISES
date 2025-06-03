#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

RPN::RPN() : _result(0) {}

RPN::RPN(const RPN &other) : _stack(other._stack), _result(other._result) {}

RPN &RPN::operator=(const RPN &other) {
    if (this != &other) {
        _stack = other._stack;
        _result = other._result;
    }
    return *this;
}

RPN::~RPN() {}

static bool isOperator(const std::string &str) {
    return (str == "+" || str == "-" || str == "*" || str == "/");
}

static bool isValidNumber(const std::string &str) {
    if (str.length() != 1) return false;
    return (str[0] >= '0' && str[0] <= '9');
}

static int convertToInt(const std::string &str) {
    if (!isValidNumber(str)) {
        throw std::runtime_error("Error");
    }
    return (str[0] - '0');
}

void RPN::evaluate(const std::string &expression) {
    std::string token;
    std::istringstream iss(expression);
    
    while (!_stack.empty()) {
        _stack.pop();
    }
    
    while (iss >> token) {
        if (isValidNumber(token)) {
            try {
                _stack.push(convertToInt(token));
            }
            catch (const std::exception &e) {
                throw std::runtime_error("Error");
            }
        }
        else if (isOperator(token)) {
            if (_stack.size() < 2) {
                throw std::runtime_error("Error");
            }
            
            int rightOperand = _stack.top();
            _stack.pop();
            int leftOperand = _stack.top();
            _stack.pop();
            
            int result;
            switch (token[0]) {
                case '+':
                    result = leftOperand + rightOperand;
                    break;
                case '-':
                    result = leftOperand - rightOperand;
                    break;
                case '*':
                    result = leftOperand * rightOperand;
                    break;
                case '/':
                    if (rightOperand == 0) {
                        throw std::runtime_error("Error");
                    }
                    result = leftOperand / rightOperand;
                    break;
                default:
                    throw std::runtime_error("Error");
            }
            
            _stack.push(result);
        }
        else {
            throw std::runtime_error("Error");
        }
    }
    
    if (_stack.size() != 1) {
        throw std::runtime_error("Error");
    }
    
    _result = _stack.top();
    std::cout << _result << std::endl;
}