#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN &obj)
{
	*this = obj;
}

RPN &RPN::operator=(const RPN &obj)
{
	(void)obj;
	return *this;
}

static int ft_stoi(const std::string &str)
{
	int num;
	std::stringstream ss(str);

	ss >> num;
	return num;
}

const char *RPN::Error::what(void) const throw()
{
	return "ERROR";
}

bool RPN::isOperator(char op)
{
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

RPN::~RPN()
{
}

double RPN::calculator(double left, double right, char op)
{
	if (op == '+')
		return (left + right);
	if (op == '-')
		return (left - right);
	if (op == '*')
		return (left * right);
	if (right == 0)
		throw RPN::Error();
	return (left / right);
}

double RPN::calculate(const std::string &str)
{
	int right;
	int left;
	int result;

	std::stringstream postfix(str);
	std::stack<int> temp;
	std::string s;
	while (postfix >> s)
	{
		if (isOperator(s[0]))
		{
			if (temp.size() < 2)
				throw Error();
			right = temp.top();
			temp.pop();
			left = temp.top();
			temp.pop();
			result = calculator(left, right, s[0]);
			temp.push(result);
		}
		else
			temp.push(ft_stoi(s));
	}
	if (temp.size() != 1)
		throw Error();
	return temp.top();
}
