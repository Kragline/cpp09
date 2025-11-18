#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <sstream>

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_dec;
public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	~PmergeMe();

	PmergeMe	&operator=(const PmergeMe &other);

	void	start(char **argv);

private:
	template <typename Container>
	void	_printContainer(const Container &cont)
	{
		for (size_t i = 0; i < cont.size(); i++)
		{
			std::cout << cont[i];
			if (i != cont.size() - 1)
				std::cout << ' ';
		}
		std::cout << std::endl;
	}
	void	_parseInput(char **argv);
};
