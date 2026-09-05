/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:10:17 by joaolive          #+#    #+#             */
/*   Updated: 2026/03/05 13:40:21 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& dbPath) {
	loadDatabase(dbPath);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		this->_database = other._database;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& dbPath) {
	std::ifstream file(dbPath.c_str());
	validate_file(file);
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		size_t sep = line.find(",");
		if (sep != std::string::npos) {
			std::string date = trim(line.substr(0, sep));
			double rate = std::strtod(trim(line.substr(sep + 1)).c_str(), NULL);
			if (isValidDate(date))
				_database[date] = rate;
		}
	}
}

void BitcoinExchange::processInput(const std::string& filename) {
	std::ifstream file(filename.c_str());
	validate_file(file);
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		if (line.empty())
			continue ;
		processLine(line);
	}
}

void BitcoinExchange::processLine(const std::string& line) {
	size_t sep = line.find('|');
	if (sep == std::string::npos) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return ;
	}
	std::string date = trim(line.substr(0, sep));
	std::string valStr = trim(line.substr(sep + 1));
	if (!isValidDate(date)) {
		std::cerr << "Error: bad input => " << date << std::endl;
		return ;
	}
	double value;
	if (!parseAndValidateValue(valStr, value, line))
		return ;
	calculateAndPrint(date, value);
}

bool BitcoinExchange::parseAndValidateValue(const std::string& valStr, double& value, const std::string& line) const {
	char* endptr;
	value = std::strtod(valStr.c_str(), &endptr);

	if (valStr.empty() || (*endptr != '\0' && !std::isspace(*endptr))) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}
	if (value < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (value > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
}

void BitcoinExchange::calculateAndPrint(const std::string& date, double value) const {
	std::map<std::string, double>::const_iterator it = _database.lower_bound(date);

	if (it == _database.end() || it->first != date) {
		if (it == _database.begin()) {
			std::cerr << "Error: date too early, no data available => " << date << std::endl;
			return ;
		}
		--it;
	}
	std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
}

void BitcoinExchange::validate_file(std::ifstream& file)
{
	if (!file.is_open())
		throw std::runtime_error("Error: " + std::string(std::strerror(errno)));
	if (file.peek() == std::ifstream::traits_type::eof())
		throw std::runtime_error("Error: Empty file");
}

std::string BitcoinExchange::trim(const std::string& str) const {
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
		return ("");
	size_t last = str.find_last_not_of(" \t\n\r");
	return (str.substr(first, (last - first + 1)));
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
	int year, month, day;
	char dash1, dash2;

	if (date.length() != 10)
		return (false);
	std::stringstream ss(date);
	if (!(ss >> year >> dash1 >> month >> dash2 >> day))
		return (false);
	if (!(dash1 == '-' && dash2 == '-' && ss.eof()))
		return (false);
	if (year < 2009 || month < 1 || month > 12 || day < 1)
		return (false);
	static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDays = daysInMonth[month - 1];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		maxDays = 29;
	if (day > maxDays)
		return (false);
	return (true);
}
