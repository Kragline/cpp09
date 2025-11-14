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

std::string	BitcoinExchange::_trimString(std::string str)
{
	size_t	start = str.find_first_not_of(" \t");
	size_t	end = str.find_last_not_of(" \t");

	if (start == std::string::npos)
		str = "";
	else
		str = str.substr(start, end - start + 1);
	return (str);
}

bool	BitcoinExchange::_isValidDate(std::string &date)
{
	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	
	std::string	y = date.substr(0, 4);
	std::string	m = date.substr(5, 2);
	std::string	d = date.substr(8, 2);

	for (size_t i = 0; i < y.size(); i++) if (!std::isdigit(y[i])) return (false);
	for (size_t i = 0; i < m.size(); i++) if (!std::isdigit(m[i])) return (false);
	for (size_t i = 0; i < d.size(); i++) if (!std::isdigit(d[i])) return (false);
	
	int	year = std::atoi(y.c_str());
	int	month = std::atoi(m.c_str());
	int	day = std::atoi(d.c_str());
	int	daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
	{
        daysInMonth[1] = 29;
	}

	if (day < 1 || day > daysInMonth[month - 1])
		return (false);
	return (true);
}

bool	BitcoinExchange::_validateNumber(std::string &sValue, std::string &line, float &fValue)
{
	std::stringstream	valueStream(sValue);
	valueStream >> fValue;

	if (valueStream.fail())
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}

	if (fValue < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (fValue > 1000)
	{
		std::cerr << "Error: too large number." << std::endl;
		return (false);
	}
	return (true);
}

std::map<std::string, float>::const_iterator	BitcoinExchange::_findDate(std::string &date)
{
	std::map<std::string, float>::const_iterator	it = _data.lower_bound(date);

	// exact match
	if (it != _data.end() && it->first == date)
		return (it);
	
	// input date is earlier than any date in _data, return an error
	if (it == _data.begin())
		return (_data.end());
	
	// input date is after any date in _data, return the last one
	if (it == _data.end())
		return (--it);
	
	// in any other case just use the closest lowest date
	return (--it);
}

void	BitcoinExchange::_processInputFile()
{
	std::string	line;

	std::getline(_inputFile, line);
	while (std::getline(_inputFile, line))
	{
		if (line.empty()) continue;

		float				fValue;
		std::string			date;
		std::string			sValue;
		std::stringstream	ss(line);

		size_t	pos = line.find('|');
        if (pos == std::string::npos)
		{
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        date = _trimString(line.substr(0, pos));
        sValue = _trimString(line.substr(pos + 1));

		if (!_validateNumber(sValue, line, fValue))
			continue;
		
		std::map<std::string, float>::const_iterator	it = _findDate(date);
		if (it == _data.end())
		{
			std::cerr << "Error: input date is earlier than any known date." << std::endl;
			continue;
		}
		std::cout << date << " => " << fValue << " = " << (fValue * it->second) << std::endl;
	}
}

void	BitcoinExchange::start(std::string inputName)
{
	_openFiles(inputName);
	_readFromCSV();
	_processInputFile();
}
