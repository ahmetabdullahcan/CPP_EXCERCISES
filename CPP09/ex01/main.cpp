#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        RPN rpn;
        try
        {
            rpn.evaluate(av[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}