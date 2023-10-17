#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){

}
BitcoinExchange::BitcoinExchange(std::string filename) : filename(filename){

}
BitcoinExchange::~BitcoinExchange(){

}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj){
	*this = obj;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &obj) {
	if (this != &obj)
	{
		this->filename = obj.filename;
		this->bitcoinData = obj.bitcoinData;
		this->date = obj.date;
		this->day = obj.day;
		this->line = obj.line;
		this->month = obj.month;
		this->value = obj.value;
		this->year = obj.year;
	}
	return (*this);
}

const char *BitcoinExchange::BadInputerrorException::what(void) const throw(){
	return ("Error: bad input Error");
}
const char *BitcoinExchange::BadValueerrorException::what(void) const throw(){
	return ("Error: bad value Error");
}
const char *BitcoinExchange::BadNumbererrorException::what(void) const throw(){
	return ("Error: bad Number Error");
}

void BitcoinExchange::execute() {
	std::fstream file;
	std::ifstream inputFile;

	file.open("data.csv");
	if (!file.is_open()) {
		std::cout << "Error: file open error" << std::endl;
		return ;
	}
	while (std::getline(file, this->line))
	{
		std::string key = this->line.substr(0, this->line.find(','));
		std::string value = this->line.erase(0, key.length() + 1);
		this->bitcoinData.insert(std::pair<std::string, std::string>(key, value));
	}
	file.close();
	inputFile.open(this->filename);
	std::string line;
	std::string date;

	if (!inputFile.is_open()) {
		std::cout << "Error: inputfile open error" << std::endl;
		return ;
	}
	std::getline(inputFile, line);
	while (std::getline(inputFile, line)) {
		if (line.length() == 0)
			continue;
		try {
			if (line.length() < 1)
				throw (BadValueerrorException());
			date = line.substr(0, line.find("|"));
			line = line.erase(0, date.length() + 2);
			strToIntConverter(date, this->day, this->month, this->year);
			this->date = dateToConverter();
			this->value = std::atof(line.c_str());
			if (this->value < 0 || this->value > 1000)
				throw (BadInputerrorException());
			std::multimap<std::string, std::string>::iterator it;
			it = this->bitcoinData.find(this->date);
			if (it == this->bitcoinData.end()) {
				--it;
				while (it != this->bitcoinData.begin())
				{
					--it;
					if (isNearestDate(it))
						break;
				}
				if (it == this->bitcoinData.begin())
					throw (BadInputerrorException());
			}
			printDate(this->date, (*it).second);
		}catch(BadInputerrorException &e) {
			std::cerr << e.what() << this->date << std::endl;
		}catch(BadValueerrorException &e) {
			std::cerr << e.what() << this->date << std::endl;
		}catch(BadNumbererrorException &e) {
			std::cerr << e.what() << this->date << std::endl;
		}
	}
}

void BitcoinExchange::printDate(std::string date, std::string exchange_rate) {
	std::cout << date << " => " << this->value << " = " << this->value * std::atof(exchange_rate.c_str()) << std::endl;
}

bool BitcoinExchange::isNearestDate(std::multimap<std::string, std::string>::iterator &it){
	int day, month, year;

	std::string date = (*it).first;
	strToIntConverter(date, day, month, year);
	if (year < this->year)
		return true;
	if (year <= this->year && month < this->month)
		return true;
	if (year <= this->year && month <= this->month && day < this->day)
		return true;
	return false;
}

void BitcoinExchange::strToIntConverter(std::string key, int &day, int &month, int &year){
	size_t pos = 0;
	size_t index = 0;
	std::string keyCopy = key;

	while ((pos = keyCopy.find("-")) != std::string::npos) {
		if (index == 0)
			year = std::atoi(keyCopy.substr(0, pos).c_str());
		else if (index == 1)
			month = std::atoi(keyCopy.substr(0, pos).c_str());
		index++;
		keyCopy.erase(0, pos + 1);
	}
	day = std::atoi(keyCopy.c_str());
	if (!year || !month || !day) {
		throw (BadValueerrorException());
	}
	if (year < 0)
		throw (BadNumbererrorException());
	if (month < 1 || month > 12)
		throw (BadNumbererrorException());
	if (day < 0 || day > 31)
		throw (BadNumbererrorException());
}

std::string BitcoinExchange::dateToConverter() {
	std::string date, year, month, day;

	year = std::to_string(this->year);
	if (this->month < 10)
		month = "0" + std::to_string(this->month);
	else
		month = std::to_string(this->month);
	if (this->day < 10)
		day = "0" + std::to_string(this->day);
	else
		day = std::to_string(this->day);
	date = year + "-" + month + "-" + day;
	return date;
}