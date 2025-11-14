#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: program takes one argument." << std::endl;
		return (1);
	}

	RPN	notation;
	notation.start(argv[1]);

	return (0);
}
