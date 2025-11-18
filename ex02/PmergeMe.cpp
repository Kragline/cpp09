#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _dec(other._dec) {}

PmergeMe::~PmergeMe() {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_dec = other._dec;
	}
	return (*this);
}

void	PmergeMe::_parseInput(char **argv)
{
	for (size_t i = 1; argv[i]; i++)
	{
		int					number;
		std::string			arg(argv[i]);
		std::stringstream	ss(arg);

		for (size_t j = 0; j < arg.size(); j++)
			if (!std::isdigit(arg[j]))
				throw std::runtime_error("Error");
		
		ss >> number;
		if (ss.fail() || number < 1)
			throw std::runtime_error("Error");
		
		if (std::find(_vec.begin(), _vec.end(), number) != _vec.end())
			throw std::runtime_error("Error");
		
		_vec.push_back(number);
		_dec.push_back(number);
	}
}

void	PmergeMe::start(char **argv)
{
	try
	{
		_parseInput(argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
}
