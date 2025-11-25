#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe::~PmergeMe() {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return (*this);
}

std::vector<size_t>	PmergeMe::_jacobsthalSequence(size_t n)
{
    std::vector<size_t>	seq;
    seq.push_back(1);
    if (n == 1) return (seq);

    size_t	j1 = 1, j2 = 1;
    while (true)
    {
        size_t	j = j1 + 2 * j2;
        if (j > n)
            break;
        seq.push_back(j);
        j2 = j1;
        j1 = j;
    }
    return (seq);
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
		_deq.push_back(number);
	}
}

void	PmergeMe::_mergeInsertSortVector(std::vector<int> &data)
{
	if (data.size() <= 1)
		return;

	std::vector<std::pair<int,int> >	pairs;
	std::vector<int> 					mainChain;
	std::vector<int> 					pend;

	for (size_t i = 0; i + 1 < data.size(); i += 2)
	{
		int	a = data[i];
		int	b = data[i + 1];
		if (a > b) std::swap(a,b);
		pairs.push_back(std::make_pair(a,b));
	}

	int		odd = -1;
	bool	hasOdd = (data.size() % 2 == 1);
	if (hasOdd)
		odd = data.back();

	for (size_t i = 0; i < pairs.size(); i++)
		mainChain.push_back(pairs[i].second);

	_mergeInsertSortVector(mainChain);

	for (size_t i = 0; i < pairs.size(); i++)
		pend.push_back(pairs[i].first);

	std::vector<size_t>	jac = _jacobsthalSequence(pend.size());

	size_t	inserted = 0;
	for (size_t i = 0; i < jac.size(); i++)
	{
		size_t idx = jac[i] - 1;
		if (idx < pend.size())
		{
			_binaryInsert(mainChain, pend[idx], mainChain.size());
			inserted++;
		}
	}

	for (size_t i = 0; i < pend.size(); i++)
	{
		if (std::find(jac.begin(), jac.end(), i + 1) == jac.end())
			_binaryInsert(mainChain, pend[i], mainChain.size());
	}

	if (hasOdd)
		_binaryInsert(mainChain, odd, mainChain.size());

	data = mainChain;
}

void	PmergeMe::_mergeInsertSortDeque(std::deque<int> &data)
{
	if (data.size() <= 1)
		return;

	std::deque<std::pair<int,int> >	pairs;
	std::deque<int>					mainChain;
	std::deque<int>					pend;

	for (size_t i = 0; i + 1 < data.size(); i += 2)
	{
		int	a = data[i];
		int	b = data[i + 1];
		if (a > b) std::swap(a,b);
		pairs.push_back(std::make_pair(a,b));
	}

	int		odd = -1;
	bool	hasOdd = (data.size() % 2 == 1);
	if (hasOdd)
		odd = data.back();

	for (size_t i = 0; i < pairs.size(); i++)
		mainChain.push_back(pairs[i].second);

	_mergeInsertSortDeque(mainChain);

	for (size_t i = 0; i < pairs.size(); i++)
		pend.push_back(pairs[i].first);

	std::vector<size_t>	jac = _jacobsthalSequence(pend.size());

	for (size_t j = 0; j < jac.size(); j++)
	{
		size_t idx = jac[j] - 1;
		if (idx < pend.size())
			_binaryInsert(mainChain, pend[idx], mainChain.size());
	}

	for (size_t i = 0; i < pend.size(); i++)
	{
		if (std::find(jac.begin(), jac.end(), i + 1) == jac.end())
			_binaryInsert(mainChain, pend[i], mainChain.size());
	}

	if (hasOdd)
		_binaryInsert(mainChain, odd, mainChain.size());

	data = mainChain;
}

void	PmergeMe::_sort()
{
	std::cout << "Before: ";
	_printContainer(_vec);

	struct timeval	start, end;

	// Vector
	gettimeofday(&start, NULL);
	_mergeInsertSortVector(_vec);
	gettimeofday(&end, NULL);
	long	vectorTime = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);

	// Deque
	gettimeofday(&start, NULL);
	_mergeInsertSortDeque(_deq);
	gettimeofday(&end, NULL);
	long	dequeTime = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);

	std::cout << "After:  ";
	_printContainer(_vec);

	std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque  : " << dequeTime << " us" << std::endl;
}

void	PmergeMe::start(char **argv)
{
	try
	{
		_parseInput(argv);
		_sort();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
