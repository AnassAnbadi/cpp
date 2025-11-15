#include "RPN.hpp"
#include <sstream>
#include <cstdlib>

RPN::RPN(void) {}

RPN::~RPN(void) {}

RPN::RPN(const RPN& other)
{
	*this = other;
}

RPN& RPN::operator=(const RPN& rhs)
{
	if (this != &rhs)
		_stack = rhs._stack;
	return *this;
}

bool RPN::evaluate(const std::string& expression)
{
	std::istringstream iss(expression);
	std::string token;
	
	while (iss >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (_stack.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return false;
			}
			
			int b = _stack.top(); _stack.pop();
			int a = _stack.top(); _stack.pop();
			int result;
			
			if (token == "+")
				result = a + b;
			else if (token == "-")
				result = a - b;
			else if (token == "*")
				result = a * b;
			else if (token == "/")
			{
				if (b == 0)
				{
					std::cerr << "Error" << std::endl;
					return false;
				}
				result = a / b;
			}
			_stack.push(result);
		}
		else if (token.find_first_not_of("0123456789") == std::string::npos)
		{
			if (token.length() > 1)
			{
				std::cerr << "Error" << std::endl;
				return false;
			}
			_stack.push(std::atoi(token.c_str()));
		}
		else
		{
			std::cerr << "Error" << std::endl;
			return false;
		}
	}
	
	if (_stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return false;
	}
	
	std::cout << _stack.top() << std::endl;
	return true;
}
