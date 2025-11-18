#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) : _inputTokens(other._inputTokens) {}

RPN::~RPN() {}

RPN	&RPN::operator=(const RPN &other)
{
	if (this != &other)
		_inputTokens = other._inputTokens;
	return (*this);
}

bool	RPN::_isOperation(std::string &token) const
{
	return (token.find_first_of("+-*/") != std::string::npos ? true : false);
}

bool	RPN::_isAllSpace(std::string &input) const
{
	for (size_t i = 0; i < input.size(); i++)
		if (!std::isspace(input[i]))
			return (false);
	return (true);
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
	if (token.size() != 1)
		return (false);
	
	if (_isOperation(token))
		return (true);
	
	if (!std::isdigit(token[0]))
		return (false);

	int	number = token[0] - '0';
	return (number < 0 || number > 9 ? false : true);
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
			throw std::runtime_error("Error");
	}
}

int	RPN::_calculate(int num1, int num2, std::string &operand) const
{
	if (operand == "+") return (num1 + num2);
	if (operand == "-") return (num1 - num2);
	if (operand == "*") return (num1 * num2);
	
	if (num2 == 0)
		throw std::runtime_error("Error");
	return (num1 / num2);
}

void	RPN::_processInput()
{
	int	num1, num2, result;

	for (std::list<std::string>::iterator it = _inputTokens.begin(); it != _inputTokens.end(); ++it)
	{
		if (_isOperation(*it))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error");
			
			num2 = _stack.top();
			_stack.pop();
			num1 = _stack.top();
			_stack.pop();

			result = _calculate(num1, num2, *it);
			_stack.push(result);
		}
		else
		{
			_stack.push((*it)[0] - '0');
		}
	}

	if (_stack.size() != 1)
        throw std::runtime_error("Error");
	std::cout << _stack.top() << std::endl;
}

void	RPN::start(std::string input)
{
	try
	{
		if (input.empty() || _isAllSpace(input))
			throw std::runtime_error("Error");

		_splitInput(input);
		_processInput();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
