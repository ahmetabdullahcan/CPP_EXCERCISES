#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src){
    *this = src;
}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    if (this != &rhs)
    {
        //do something later
        return *this;
    }
    return *this;
}

void BitcoinExchange::readDataFromInputFile(const std::string &filename)
{
    std::ifstream myFile(filename.c_str());
    
    if (!myFile.is_open())
    {
        throw std::runtime_error("Error: could not open file.");
    }
    std::stringstream buffer;
    buffer << myFile.rdbuf();
    this->_rawFile = buffer.str();
    myFile.close();
}




static bool checkFirstLine(const std::string &line){
    return (line == "data | value\n");
}

static bool isNotInteger(const std::string &line)
{
    for (size_t i = 0; i < line.length(); i++)
    {
        if (line[i] < '0' || line[i] > '9')
            return true;
    }
    return false;   
}

static bool isNotFloat(const std::string &line)
{
    for (size_t i = 0; i < line.length(); i++)
    {
        if ((line[i] < '0' || line[i] > '9') && (line[i] != '.'))
            return true;
    }
    return false;   
}

static std::string rtrim(const std::string& s) {
    std::string result = s;
    std::string::size_type end = result.size();

    while (end > 0 && std::isspace(static_cast<unsigned char>(result[end - 1]))) {
        --end;
    }
    result.erase(end);
    return result;
}



static std::string ltrim(const std::string& s) {
    std::string::size_type start = 0;

    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    return s.substr(start);
}

static std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
}

static int stringToInt(const std::string &line)
{
    std::stringstream ss(line);
    int num = 0;
    ss >> num;

    if (ss.fail() || !ss.eof()) {
        throw std::invalid_argument("error");
    }

    return num;
}

static bool checkDateExists(const std::string &line)
{
    int year = stringToInt(line.substr(0,4));
    int month = stringToInt(line.substr(5,2));
    int day = stringToInt(line.substr(8,2));

    if (day > 31 || month > 12 || year > 2022 || year < 2009 || month < 1 || day < 1)
        return (true);
    
    int maxday = 29;
    if (month == 3 || month == 6 || month == 9 || month == 11)
        maxday = 30;
    else if (month != 2)
        maxday = 31;
    
    if (day > maxday)
        return (true);
    if (month == 2 && day <= 29)
    {
        if (year % 400 == 0)
            return (false);
        else if (year % 100 == 0)
            return (true);
        else if (year % 4 == 0)
            return (false);
        else if (day == 29)
            return (true);
    }
    return (false);    
}


static bool checkValidDate(const std::string &line){
    std::string date;

    date = rtrim(line.substr(0, line.find('|') - 1));
    
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return true;

    if (isNotInteger(date.substr(0,4)) || isNotInteger(date.substr(5,2)) || isNotInteger(date.substr(8,2)))
    {
        return (true);
    }
    if (checkDateExists(date))
    {
        return (true);
    }
    return (false);
}


static bool checkValidAmount(const std::string &line)
{
    std::string amount = line.substr(line.find('|') + 2);

    if (isNotFloat(amount))
        return (true);
    return (false);
}

static bool checkNegativeAmount(std::string &line)
{
    std::string amount = line.substr(line.find('|') + 2, line.length() - line.find('|') + 2);
    if (amount[0] == '-')
        return (true);

    return (false);
}

void BitcoinExchange::processInputFile()
{
    std::istringstream  iss(this->_rawFile);
    std::string         row;

    std::getline(iss, row);
    if (checkFirstLine(row)){
        throw std::runtime_error("Error: first line must be 'data | value'");
    }
    while (std::getline(iss, row)){
        std::string temp = trim(row);
        if (temp.find('|') == std::string::npos || checkValidDate(temp)){
            std::string errorMessage = "Error: bad input => " + row;
            std::cerr << errorMessage << std::endl;
        }
        else if (checkNegativeAmount(temp))
        {
            std::cerr << "Error: not a positive number." << std::endl;
        }
        else if(checkValidAmount(temp))
        {
            std::string errorMessage = "Error: bad input => " + row;
            std::cerr << errorMessage << std::endl;
        }
    }
}
