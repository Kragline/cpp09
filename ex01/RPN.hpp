#pragma once

#include <stack>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>

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
	bool	_tokenIsValid(std::string &token);
	
	void	_splitInput(std::string &input);
	void	_processInout();
};
