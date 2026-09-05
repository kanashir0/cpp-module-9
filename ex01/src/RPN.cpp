/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:33 by joaolive          #+#    #+#             */
/*   Updated: 2026/03/05 14:35:12 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) {
	*this = other;
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other)
		this->_data = other._data;
	return (*this);
}

RPN::~RPN() {}

void RPN::calculate(const std::string& args) {
	std::istringstream ss(args);
	std::string token;

	while (!_data.empty())
		_data.pop();
	while (ss >> token) {
		if (token.length() != 1)
			throw (std::invalid_argument("Error"));
		if (std::isdigit(token[0]))
			_data.push(token[0] - '0');
		else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
			executeOperation(token[0]);
		else
			throw (std::invalid_argument("Error"));
	}
	if (_data.size() == 1)
		std::cout << _data.top() << std::endl;
	else
		throw (std::invalid_argument("Error"));
}

void RPN::executeOperation(char op) {
	if (_data.size() < 2)
		throw (std::invalid_argument("Error"));
	int right = _data.top();
	_data.pop();
	int left = _data.top();
	_data.pop();
	int result = 0;
	if (op == '+')
		result = left + right;
	else if (op == '-')
		result = left - right;
	else if (op == '*')
		result = left * right;
	else if (op == '/') {
		if (right == 0)
			throw (std::invalid_argument("Error"));
		result = left / right;
	}
	_data.push(result);
}
