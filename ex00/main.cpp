#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2){
		std::cout << "file error" << std::endl;
		return (1);
	}
	std::string filename(argv[1]);
	BitcoinExchange file(filename);
	file.execute();
	return (0);
}