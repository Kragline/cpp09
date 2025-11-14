#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>
#include <cctype>

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
	void	_openFiles(std::string &inputName);
	bool	_validateNumber(std::string &sValue, std::string &line, float &fValue);
	bool	_isValidDate(std::string &date);

	std::string	_trimString(std::string str);
	std::map<std::string, float>::const_iterator	_findDate(std::string &date);

	void	_readFromCSV();
	void	_processInputFile();
};
