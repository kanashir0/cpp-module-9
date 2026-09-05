/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:24:35 by naharumi          #+#    #+#             */
/*   Updated: 2025/07/31 14:37:41 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av) {
	if (ac < 2) {
		std::cerr << "Usage: " << av[0] << " <numbers>" << std::endl;
		return 1;
	}
	
	PmergeMe pm;
	try {
		pm.processInput(ac, av);
		pm.sortVector();
		pm.sortDeque();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
