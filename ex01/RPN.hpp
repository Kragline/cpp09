#pragma once

#include <stack>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

class RPN
{
private:
	std::vector<std::string>	_inputTokens;
	std::stack<int>				_stack;
public:
	RPN();
	RPN(const RPN &other);
	~RPN();

	RPN	&operator=(const RPN &other);

	void	start(std::string input);
private:
	bool	_isOperation(std::string &token) const ;
	bool	_tokenIsValid(std::string &token) const ;
	bool	_convertNumber(std::string &sValue, int &value) const ;
	void	_trimToken(std::string &token) const ;
	
	int		_calculate(int num1, int num2, std::string &operand) const ;
	
	void	_splitInput(std::string &input);
	void	_processInput();
};
