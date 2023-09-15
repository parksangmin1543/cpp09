#include <iostream>
#include <stack>
#include <exception>
#include <sstream>

class RPN
{
private:
	RPN();
	RPN(const RPN &obj);
	RPN &operator=(const RPN &obj);

public:
	~RPN();

	static bool isOperator(char op);
	static double calculate(const std::string &str);
	static double calculator(double a, double b, char op);

	class Error : public std::exception
	{
	public:
		const char *what() const throw();
	};
};