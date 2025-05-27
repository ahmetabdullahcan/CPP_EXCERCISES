#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>


class RPN {
    private:
        std::stack<int> _stack;
        int _result;
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();

        void evaluate(const std::string &expression);
};


#endif