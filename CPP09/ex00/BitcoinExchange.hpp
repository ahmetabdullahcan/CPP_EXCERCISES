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
    std::map<int, int> _dateData;
    std::map<std::string, float> _data;
    std::map<std::string, float> _inputData;
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &src);
    BitcoinExchange &operator=(const BitcoinExchange &rhs);
    ~BitcoinExchange();

    void readDataFromInputFile(const std::string &filename);
    void processInputFile();
    void fillDateData();
    void printExchangeRate(const std::string &date, const std::string &value);
    void printError(const std::string &errorMessage);
};


#endif