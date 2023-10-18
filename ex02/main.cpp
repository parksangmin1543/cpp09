#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc <= 2){
		std::cout << "argc error" << std::endl;
		return 1;
	}
	PmergeMe pm;

	try {
		for (int i = 1; i < argc; i++) {
			if (std::string(argv[i]).find_first_not_of("0123456789 ") != std::string::npos)
				throw PmergeMe::ErrorException();
			for (int j = 0; j < int(strlen(argv[i])); j++)
				if (std::isspace(argv[i][j]))
					throw PmergeMe::ErrorException();
		}
		std::vector<size_t>temp;
		for (int i = 1; i < argc; i += 1)
			temp.push_back(pm.ft_stoi(argv[i]));

		// std::vector<size_t>::iterator it_a;
		// std::vector<size_t>::iterator it_b;
		// for (it_a = temp.begin(); it_a != temp.end(); it_a++) {
		// 	for (it_b = it_a + 1; it_b != temp.end(); it_b++) {
		// 		if (*it_a == *it_b)
		// 			throw PmergeMe::ErrorException();
		// 	}
		// }
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	pm.sortVec(argc, argv);
	pm.sortList(argc, argv);

	return 0;
}