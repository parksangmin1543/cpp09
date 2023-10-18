#pragma once

#include <exception>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <list>

#define MS 1000000

class PmergeMe {
	private:
		PmergeMe(const PmergeMe &obj);
		PmergeMe &operator=(const PmergeMe &obj);

	public:
		PmergeMe();
		~PmergeMe();
		void sortVec(int argc, char **argv);
		void sortList(int argc, char **argv);
		size_t ft_stoi(const std::string &str);

		class ErrorException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};