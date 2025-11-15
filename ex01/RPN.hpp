#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <iostream>

class RPN
{
private:
	std::stack<int> _stack;
	
	RPN(const RPN& other);
	RPN& operator=(const RPN& rhs);

public:
	RPN(void);
	~RPN(void);
	
	bool evaluate(const std::string& expression);
};

#endif
