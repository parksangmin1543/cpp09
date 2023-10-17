#pragma once

#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange
{
private:
	// std::map<std::string, float> bitcoinData;
	std::map<std::string, std::string> bitcoinData;
	std::string filename;
	std::string line;
	std::string date;
	int year;
	int month;
	int day;
	float value;
	BitcoinExchange();
	void strToIntConverter(std::string key, int &day, int &month, int &year);
	std::string dateToConverter();
	bool isNearestDate(std::multimap<std::string, std::string>::iterator &it);
	void printDate(std::string date, std::string exchange_rate);
public:
	BitcoinExchange(std::string filename);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &obj);
	BitcoinExchange &operator=(const BitcoinExchange &obj);

	void execute();

	class BadInputerrorException : std::exception{
		public:
			const char *what() const throw();
	};
	class BadValueerrorException : std::exception{
		public:
			const char *what() const throw();
	};
	class BadNumbererrorException : std::exception{
		public:
			const char *what() const throw();
	};
};