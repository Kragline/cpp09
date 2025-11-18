#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: program takes one and more arguments." << std::endl;
		return (1);
	}

	PmergeMe	pm;
	pm.start(argv);

	return (0);
}
