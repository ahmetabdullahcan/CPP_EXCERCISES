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
        this->_data = rhs._data;
        this->_dateData = rhs._dateData;
        this->_inputData = rhs._inputData;
        this->_rawFile = rhs._rawFile;
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
    return (line == "date | value");
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
    bool hasDot = false;
    for (size_t i = 0; i < line.length(); i++)
    {
        if (line[i] == '.')
        {
            if (hasDot)
                return true; // İkinci nokta
            hasDot = true;
        }
        else if (line[i] < '0' || line[i] > '9')
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

static float stringToFloat(const std::string &line)
{
    std::stringstream ss(line);
    float num = 0.0f;
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
    if (month == 4 || month == 6 || month == 9 || month == 11)
        maxday = 30;
    else if (month != 2)
        maxday = 31;
    
    if (day > maxday)
        return (true);
    if (month == 2 && day == 29)
    {
        if (year % 400 == 0)
            return (false);
        else if (year % 100 == 0)
            return (true);
        else if (year % 4 == 0)
            return (false);
        return (true);
    }
    return (false);    
}

static bool checkValidDate(const std::string &line){
    std::string::size_type pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return true;
        
    std::string date = trim(line.substr(0, pipePos));
    
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
    std::string::size_type pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return true;
        
    std::string amount = trim(line.substr(pipePos + 1));

    if (isNotFloat(amount))
        return (true);
    return (false);
}

static bool checkNegativeAmount(const std::string &line)
{
    std::string::size_type pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return false;
        
    std::string amount = trim(line.substr(pipePos + 1));
    if (!amount.empty() && amount[0] == '-')
        return (true);

    return (false);
}

static bool checkAmountTooLarge(const std::string &line)
{
    std::string::size_type pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return false;
        
    std::string amountStr = trim(line.substr(pipePos + 1));
    try {
        float amount = stringToFloat(amountStr);
        return (amount > 1000.0f);
    } catch (...) {
        return false;
    }
}

void BitcoinExchange::fillDataMap()
{
    std::ifstream myFile("data.csv");
    if (!myFile.is_open())
    {
        throw std::runtime_error("Error: could not open data.csv file.");
    }
    std::string row;
    bool isFirstLine = true;
    while (std::getline(myFile, row))
    {
        if (isFirstLine)
        {
            isFirstLine = false;
            continue;
        }
        std::string::size_type commaPos = row.find(',');
        if (commaPos == std::string::npos)
            continue;
            
        std::string date = trim(row.substr(0, commaPos));
        std::string value = trim(row.substr(commaPos + 1));
        
        this->_data[date] = stringToFloat(value);
    }
    myFile.close();
    
    // String tarihlerini integer anahtarlara dönüştür
    for (std::map<std::string, float>::iterator it = this->_data.begin(); 
         it != this->_data.end(); ++it)
    {
        std::string date = it->first;
        float value = it->second;
        int year = stringToInt(date.substr(0, 4));
        int month = stringToInt(date.substr(5, 2));
        int day = stringToInt(date.substr(8, 2));
        int dateKey = year * 10000 + month * 100 + day;
        
        this->_dateData[dateKey] = value;
    }
}

void BitcoinExchange::processInputFile()
{
    std::istringstream iss(this->_rawFile);
    std::string row;

    if (!std::getline(iss, row))
    {
        throw std::runtime_error("Error: empty file");
    }
    
    std::string trimmedFirstLine = trim(row);
    if (checkFirstLine(trimmedFirstLine)){
        throw std::runtime_error("Error: first line must be 'date | value'");
    }
    
    this->fillDataMap(); 
    
    while (std::getline(iss, row)){
        std::string temp = trim(row);
        
        if (temp.empty())
            continue;
            
        if (temp.find('|') == std::string::npos)
        {
            std::cerr << "Error: bad input => " << temp << std::endl;
            continue;
        }
        
        if (checkValidDate(temp))
        {
            std::cerr << "Error: bad input => " << temp << std::endl;
            continue;
        }
        
        if (checkNegativeAmount(temp))
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        
        if (checkValidAmount(temp))
        {
            std::cerr << "Error: bad input => " << temp << std::endl;
            continue;
        }
        
        if (checkAmountTooLarge(temp))
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        
        // Geçerli veri - işle
        std::string::size_type pipePos = temp.find('|');
        std::string date = trim(temp.substr(0, pipePos));
        std::string amountStr = trim(temp.substr(pipePos + 1));
        float amount = stringToFloat(amountStr);
        
        int year = stringToInt(date.substr(0, 4));
        int month = stringToInt(date.substr(5, 2));
        int day = stringToInt(date.substr(8, 2));
        int dateKey = year * 10000 + month * 100 + day;
        
        // Tam eşleşme ara
        std::map<int, float>::iterator exactMatch = this->_dateData.find(dateKey);
        if (exactMatch != this->_dateData.end())
        {
            float exchangeRate = exactMatch->second;
            float result = amount * exchangeRate;
            std::cout << date << " => " << amount << " = " << result << std::endl;
        }
        else
        {
            // En yakın önceki tarihi bul
            std::map<int, float>::iterator it = this->_dateData.lower_bound(dateKey);
            if (it != this->_dateData.begin())
            {
                --it;
                float exchangeRate = it->second;
                float result = amount * exchangeRate;
                std::cout << date << " => " << amount << " = " << result << std::endl;
            }
            else
            {
                std::cerr << "Error: no data available for date " << date << std::endl;
            }
        }
    }
}