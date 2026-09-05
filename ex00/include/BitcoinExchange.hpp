/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 11:35:28 by joaolive          #+#    #+#             */
/*   Updated: 2026/09/05 11:33:26 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <stdexcept>

class BitcoinExchange {
	private:
		std::map<std::string, double> _database;
		std::string trim(const std::string& str) const;
		void validate_file(std::ifstream& file);
		bool isValidDate(const std::string& date) const;
		void loadDatabase(const std::string& dbPath);
		void processLine(const std::string& line);
		bool parseAndValidateValue(const std::string& valStr, double& value, const std::string& line) const;
		void calculateAndPrint(const std::string& date, double value) const;
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& dbPath);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void processInput(const std::string& filename);
};

