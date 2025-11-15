#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	if (this != &rhs)
		_exchangeRates = rhs._exchangeRates;
	return *this;
}

bool BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		return false;
	
	std::string line;
	std::getline(file, line);
	
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		
		std::istringstream iss(line);
		std::string date;
		std::string comma;
		float rate;
		
		if (std::getline(iss, date, ',') && iss >> rate)
		{
			date = date.substr(0, date.find_last_not_of(" \t") + 1);
			_exchangeRates[date] = rate;
		}
	}
	file.close();
	return true;
}

float BitcoinExchange::getRate(const std::string& date) const
{
	std::map<std::string, float>::const_iterator it = _exchangeRates.find(date);
	
	if (it != _exchangeRates.end())
		return it->second;
	
	it = _exchangeRates.lower_bound(date);
	
	if (it == _exchangeRates.begin())
		return -1;
	
	--it;
	return it->second;
}

bool isValidDate(const std::string& date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	
	if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	
	return true;
}

void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	
	std::string line;
	std::getline(file, line);
	
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		
		std::string dateStr = line.substr(0, pipePos);
		std::string valueStr = line.substr(pipePos + 1);
		
		dateStr = dateStr.substr(0, dateStr.find_last_not_of(" \t") + 1);
		valueStr = valueStr.substr(valueStr.find_first_not_of(" \t"));
		valueStr = valueStr.substr(0, valueStr.find_last_not_of(" \t") + 1);
		
		if (!isValidDate(dateStr))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		
		char* endptr;
		float value = std::strtof(valueStr.c_str(), &endptr);
		
		if (*endptr != '\0')
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		
		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		
		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		
		float rate = getRate(dateStr);
		if (rate == -1)
		{
			std::cout << "Error: bad input => " << dateStr << std::endl;
			continue;
		}
		
		float result = value * rate;
		std::cout << dateStr << " => " << value << " = " << result << std::endl;
	}
	file.close();
}
