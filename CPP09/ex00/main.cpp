#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Invalid use of program. Valid use is ./btc <filename>" << std::endl;
        return (1);
    }
    BitcoinExchange btc;

    try
    {
        btc.readDataFromInputFile(av[1]);
        btc.processInputFile();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return(1);
    }
}