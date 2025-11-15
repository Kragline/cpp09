#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <stdexcept>

class BitcoinExchange
{
private:
	std::map<std::string, float>	_data;
	std::ifstream					_inputFile;
	std::ifstream					_csvFile;
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	~BitcoinExchange();

	BitcoinExchange	&operator=(const BitcoinExchange &other);

	void	start(std::string inputName);
private:

	template <typename T>
	bool	_convertNumber(std::string sValue, T &value) const
	{
		std::stringstream	valueStream(sValue);
		valueStream >> value;

		return (valueStream.fail() ? false : true);
	}

	void	_openFiles(std::string &inputName);
	bool	_isValidNumber(std::string &sValue, std::string &line, float &fValue) const ;
	bool	_isValidDate(std::string &sValue, std::string &line) const ;

	std::string	_trimString(std::string str) const ;
	std::map<std::string, float>::const_iterator	_findDate(std::string &sValue) const ;

	void	_readFromCSV();
	void	_processInputFile();
};
