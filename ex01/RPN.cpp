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

bool	RPN::_tokenIsValid(std::string &token)
{
	(void)token;
	return (true);
}

void	RPN::_splitInput(std::string &input)
{
	std::string			token;
	std::stringstream	ss(input);

	while (std::getline(ss, token, ' '))
	{
		if (_tokenIsValid(token))
			_inputTokens.push_back(token);
		else
		{
			std::cerr << "Error" << std::endl;
			exit(1);
		}
	}
}

void	RPN::_processInout()
{

}

void	RPN::start(std::string input)
{
	if (input.find_first_not_of(" 0123456789+-*/") != std::string::npos)
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	_splitInput(input);
	_processInout();
}
