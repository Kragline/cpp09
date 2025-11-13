#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}

BitcoinExchange::~BitcoinExchange()
{
	_inputFile.close();
	_csvFile.close();
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
	return (*this);
}

void	BitcoinExchange::_openFiles(std::string &inputName)
{
	_inputFile.open(inputName.c_str());
	if (!_inputFile.is_open())
	{
		std::cerr << "Error: failed to open " << inputName << " file." << std::endl;
		exit(1);
	}

	_csvFile.open("data.csv");
	if (!_inputFile.is_open())
	{
		std::cerr << "Error: failed to open data.csv file." << std::endl;
		_inputFile.close();
		exit(1);
	}
}

void	BitcoinExchange::_readFromCSV()
{
	std::string	line;

	std::getline(_csvFile, line);
	while (std::getline(_csvFile, line))
	{
		if (line.empty()) continue;

		float				fValue;
		std::string			date;
		std::string			sValue;
		std::stringstream	ss(line);

		if (!std::getline(ss, date, ',')) continue;
    	if (!std::getline(ss, sValue)) continue;

		std::stringstream	valueStream(sValue);
		valueStream >> fValue;

		if (valueStream.fail())
		{
			std::cerr << "Error: invalid value in line -> " << line << std::endl;
			continue;
		}
		_data[date] = fValue;
	}
}

void	BitcoinExchange::start(std::string inputName)
{
	_openFiles(inputName);
	_readFromCSV();

}

