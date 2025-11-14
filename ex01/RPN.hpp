#pragma once

#include <stack>
#include <iostream>

class RPN
{
private:
	// TODO
public:
	RPN();
	RPN(const RPN &other);
	~RPN();

	RPN	&operator=(const RPN &other);

	void	start(std::string input);
};
