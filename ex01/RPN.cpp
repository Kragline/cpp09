#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other)
{
	(void)other;	
}

RPN::~RPN() {}

RPN	&RPN::operator=(const RPN &other)
{
	(void)other;
	return (*this);
}

void	RPN::start(std::string input)
{
	(void)input;
}
