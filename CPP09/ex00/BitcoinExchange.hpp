#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <exception>


class BitcoinExchange
{
private:
    std::string _rawFile;
    std::map<std::string, float> _data;
    std::map<int, float> _dateData;
    std::map<int, float> _inputData;
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &src);
    BitcoinExchange &operator=(const BitcoinExchange &rhs);
    ~BitcoinExchange();

    void readDataFromInputFile(const std::string &filename);
    void processInputFile();
    void fillDataMap();
};


#endif