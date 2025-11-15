#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>

class BitcoinExchange
{
private:
	std::map<std::string, float> _exchangeRates;
	
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& rhs);

public:
	BitcoinExchange(void);
	~BitcoinExchange(void);
	
	bool loadDatabase(const std::string& filename);
	void processInput(const std::string& filename);
	float getRate(const std::string& date) const;
};

#endif
