#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <ctime>
#include <sys/time.h>

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;
public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	~PmergeMe();

	PmergeMe	&operator=(const PmergeMe &other);

	void	start(char **argv);

private:
	template <typename T>
	void	_printContainer(const T &container)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			std::cout << container[i];
			if (i != container.size() - 1)
				std::cout << ' ';
		}
		std::cout << std::endl;
	}

	template<typename T>
	void	_binaryInsert(T &container, int value, size_t high)
	{
		size_t	left = 0;
		size_t	right = high;

		while (left < right)
		{
			size_t	mid = (left + right) / 2;
			if (container[mid] < value)
				left = mid + 1;
			else
				right = mid;
		}
		container.insert(container.begin() + left, value);
	}

	void				_parseInput(char **argv);
	std::vector<size_t>	_jacobsthalSequence(size_t n);
	void				_mergeInsertSortVector(std::vector<int> &data);
	void				_mergeInsertSortDeque(std::deque<int> &data);
	void				_sort();
};
