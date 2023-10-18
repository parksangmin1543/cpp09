#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
	
}

PmergeMe::~PmergeMe(){
	
}

const char* PmergeMe::ErrorException::what() const throw() {
	return "Error";
}

size_t PmergeMe::ft_stoi(const std::string &str)
{
	size_t num;
	std::stringstream ss(str);

	ss >> num;
	return num;
}

void printVec(std::vector<size_t>& vec) {
	std::vector<size_t>::const_iterator it;
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

std::vector<size_t> mergeVector(std::vector<size_t> &left, std::vector<size_t> &right) {
	std::vector<size_t> result;

	while (!left.empty() && !right.empty()) {
		if (left.front() <= right.front()) {
			result.push_back(left.front());
			left.erase(left.begin());
		}
		else {
			result.push_back(right.front());
			right.erase(right.begin());
		}
	}
	while (!left.empty()) {
		result.push_back(left.front());
		left.erase(left.begin());
	}
	while (!right.empty()) {
		result.push_back(right.front());
		right.erase(right.begin());
	}
	return result;
}

std::vector<size_t> mergeInsertVec(std::vector<size_t> &vec) {
	if (vec.size() <= 1) {
		return vec;
	}

	size_t mid = vec.size() / 2;

	std::vector<size_t> left(vec.begin(), vec.begin() + mid);
	std::vector<size_t> right(vec.begin() + mid, vec.end());

	left = mergeInsertVec(left);
	right = mergeInsertVec(right);

	return mergeVector(left, right);
}

size_t upperBound(std::vector<size_t> &vec, size_t key) {
	size_t start = 0;
	size_t mid = vec.size();
	size_t end = vec.size();

	while (end - start > 0) {
		mid = (start + end) / 2;

		if(vec[mid] <= key) {
			start = mid + 1;
		} else {
			end = mid;
		}
	}
	return end + 1;
}

std::vector<size_t> fordJohnsonVec(std::vector<size_t> &vec) {
	if (vec.size() <= 1) {
		return vec;
	}
	size_t finshIndex = 0;
	size_t vecSize = vec.size();
	bool odd = false;

	if (vecSize % 2 != 0) {
		finshIndex = vec.back();
		odd = true;
		vec.pop_back();
		vecSize--;
	}

	std::vector<size_t>::iterator it;
	size_t temp = 0;
	for (it = vec.begin(); it != vec.end() - 2; it += 2) {
		if (*it <= *(it + 1)) {
			temp = *it;
			*it = *(it + 1);
			*(it + 1) = temp;
		}
	}

	std::vector<size_t> first, second;
	for (size_t i = 0; i < vecSize; i++) {
		if (i % 2 == 0)
			first.push_back(vec.at(i));
		else
			second.push_back(vec.at(i));
	}
	first = mergeInsertVec(first);

	for (size_t i = 0; i < second.size(); i++) {
		std::vector<size_t>::iterator it = first.begin();
		size_t key = upperBound(first, second.at(i));
		first.insert(it + key - 1, second[i]);
	}

	if (odd) {
		std::vector<size_t>::iterator it = first.begin();
		size_t key = upperBound(first, finshIndex);
		first.insert(it + key - 1, finshIndex);
	}

	return first;
}

void PmergeMe::sortVec(int argc, char **argv){
	std::vector<size_t> vec;

	for (int i = 1; i < argc; i++)
		vec.push_back(ft_stoi(argv[i]));
	
	std::cout << "vec Before: ";
	printVec(vec);

	std::clock_t start = std::clock();

	// vec = mergeInsertVec(vec);
	vec = fordJohnsonVec(vec);

	double time = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MS;
	std::cout << "vec After: ";
	printVec(vec);

	std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector<size_t> : " << time << " us" << std::endl; 
}
//---------------------------------------------------------------------------------------------------------------------
void printList(std::list<size_t>& List) {
	std::list<size_t>::const_iterator it;
	for (it = List.begin(); it != List.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

std::list<size_t> mergeList(std::list<size_t> &left, std::list<size_t> &right) {
	std::list<size_t> result;

	while (!left.empty() && !right.empty()) {
		if (left.front() <= right.front()) {
			result.push_back(left.front());
			left.erase(left.begin());
		}
		else {
			result.push_back(right.front());
			right.erase(right.begin());
		}
	}
	while (!left.empty()) {
		result.push_back(left.front());
		left.erase(left.begin());
	}
	while (!right.empty()) {
		result.push_back(right.front());
		right.erase(right.begin());
	}
	return result;
}

std::list<size_t> mergeInsertList(std::list<size_t> &List) {
	if (List.size() <= 1) {
		return List;
	}

	size_t mid = List.size() / 2;

	std::list<size_t>::iterator it = List.begin();
	for (size_t i = 0; i < mid; i++){
		it++;
	}

	std::list<size_t> left(List.begin(), it);
	std::list<size_t> right(it, List.end());

	left = mergeInsertList(left);
	right = mergeInsertList(right);

	return mergeList(left, right);
}

size_t upperBoundList(std::list<size_t> &List, size_t key) {
	std::list<size_t>::iterator it = List.begin();

	for (size_t i = 0; i < List.size(); i++) {
		if (key < *it){
			return i;
		}
	}
	return List.size();
}

std::list<size_t> fordJohnsonList(std::list<size_t> &List) {
	if (List.size() <= 1) {
		return List;
	}
	size_t finshIndex = 0;
	size_t ListSize = List.size();
	bool odd = false;

	if (ListSize % 2 != 0) {
		finshIndex = List.back();
		odd = true;
		List.pop_back();
		ListSize--;
	}

	std::list<size_t>::iterator it = List.begin();
	size_t temp = 0;

	for (size_t i = 0; i < List.size() - 2; i += 2) {
		std::list<size_t>::iterator next_it=it; 
		++next_it;
		if (*it <= *next_it) {
			temp = *it;
			*it = *next_it;
			*next_it = temp;
		}
		it++;
		it++;
	}

	std::list<size_t> first, second;

	size_t i = 0;
	for (it = List.begin(); it != List.end(); i++) {
		if (i % 2 == 0)
			first.push_back(*it);
		else
			second.push_back(*it);
		it++;
	}
	
	first = mergeInsertList(first);

	std::list<size_t>::iterator iter_first = first.begin(), iter_second = second.begin();

	while (iter_first!=first.end() && iter_second!=second.end()) {
		size_t key = *iter_second;
		while (iter_first != first.end() && key > *iter_first) {
			iter_first++;
		}
		first.insert(iter_first, key);
		iter_first = first.begin();
		iter_second++;
	}

	if (odd) {
		std::list<size_t>::iterator it = first.begin();
		while (it != first.end() && finshIndex > *it)
			it++;
		first.insert(it, finshIndex);
	}

	return first;
}

void PmergeMe::sortList(int argc, char **argv){
	std::list<size_t> List;

	for (int i = 1; i < argc; i++) {
		List.push_back(ft_stoi(argv[i]));
	}
	
	std::cout << "List Before: ";
	printList(List);

	std::clock_t start = std::clock();

	// List = mergeInsertList(List);
	List = fordJohnsonList(List);
	double time = static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * MS;
	std::cout << "List After: ";
	printList(List);

	std::cout << "Time to process a range of " << argc - 1 << " elements with std::list<size_t> : " << time << " us" << std::endl; 
}