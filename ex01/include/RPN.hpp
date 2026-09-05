/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:56 by joaolive          #+#    #+#             */
/*   Updated: 2026/03/05 14:36:54 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

class RPN {
	private:
		std::stack<int> _data;
		void executeOperation(char op);
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		void calculate(const std::string& args);
};
