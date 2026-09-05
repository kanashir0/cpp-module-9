/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:34:36 by joaolive          #+#    #+#             */
/*   Updated: 2026/03/05 14:33:10 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv) {
	RPN rpn;
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try {
		rpn.calculate(std::string(argv[1]));
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
