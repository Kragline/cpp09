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

bool	RPN::_isOperation(std::string &token) const
{
	if (token.size() != 1)
		return (false);
	return (token.find_first_of("+-*/") != std::string::npos ? true : false);
}

bool	RPN::_convertNumber(std::string &sValue, int &value) const
{
	std::stringstream	valueStream(sValue);
	valueStream >> value;

	return (valueStream.fail() ? false : true);
}

void	RPN::_trimToken(std::string &token) const
{
	size_t	start = token.find_first_not_of(" \t");
	size_t	end = token.find_last_not_of(" \t");

	if (start == std::string::npos)
		token = "";
	else
		token = token.substr(start, end - start + 1);
}

bool	RPN::_tokenIsValid(std::string &token) const
{
	int	number;

	if (_isOperation(token))
		return (true);
	
	if (!_convertNumber(token, number))
		return (false);
	return (number >= 10 ? false : true);
}

void	RPN::_splitInput(std::string &input)
{
	std::string			token;
	std::stringstream	ss(input);

	while (std::getline(ss, token, ' '))
	{
		_trimToken(token);
		if (token.empty())
			continue;
		
		if (_tokenIsValid(token))
			_inputTokens.push_back(token);
		else
		{
			std::cerr << "Error" << std::endl;
			exit(1);
		}
	}
}

int	RPN::_calculate(int num1, int num2, std::string &operand) const
{
	if (operand == "+")
		return (num1 + num2);
	if (operand == "-")
		return (num1 - num2);
	if (operand == "*")
		return (num1 * num2);
	
	if (num2 == 0)
		throw std::runtime_error("Error");		
	return (num1 / num2);
}

void	RPN::_processInput()
{
	int	num, num1, num2, result;

	for (size_t i = 0; i < _inputTokens.size(); i++)
	{
		if (_isOperation(_inputTokens[i]))
		{
			if (_stack.size() < 2)
			{
				std::cerr << "Error process" << std::endl;
				exit(1);
			}
			num2 = _stack.top();
			_stack.pop();
			num1 = _stack.top();
			_stack.pop();
			try
			{
				result = _calculate(num1, num2, _inputTokens[i]);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
				exit(1);
			}
			_stack.push(result);
		}
		else
		{
			_convertNumber(_inputTokens[i], num);
			_stack.push(num);
		}
	}
	std::cout << _stack.top() << std::endl;
}

void	RPN::start(std::string input)
{
	if (input.find_first_not_of(" 0123456789+-*/") != std::string::npos)
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	_splitInput(input);
	_processInput();
}
