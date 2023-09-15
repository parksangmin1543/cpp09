#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		return (0);
	}
	try
	{
		std::cout << RPN::calculate(av[1]) << "\n";
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
	}
	return (0);
}