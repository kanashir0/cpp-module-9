/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:49:09 by joaolive          #+#    #+#             */
/*   Updated: 2026/03/09 10:37:37 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>
#include <stdexcept>
#include <deque>

double getElapsedTime(struct timeval start, struct timeval end) {
	return (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
}

std::vector<int> parseArguments(int argc, char** argv) {
	std::vector<int> vec;
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg.empty())
			throw std::invalid_argument("Error: empty argument.");

		for (size_t j = 0; j < arg.length(); ++j) {
			if (!isdigit(arg[j]) && !(j == 0 && arg[j] == '+')) {
				throw std::invalid_argument("Error: invalid characters found.");
			}
		}

		long val = std::atol(arg.c_str());
		if (val < 0 || val > 2147483647) {
			throw std::out_of_range("Error: number out of positive integer limits.");
		}
		vec.push_back(static_cast<int>(val));
	}
	return (vec);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Error: No sequence provided." << std::endl;
		std::cerr << "Usage: ./PmergeMe [positive_integers...]" << std::endl;
		return (1);
	}

	try {
		std::vector<int> vec = parseArguments(argc, argv);
		std::deque<int> deq(vec.begin(), vec.end());

		PmergeMe::printContainer(vec, "Before: ");

		struct timeval start, end;

		gettimeofday(&start, NULL);
		PmergeMe::fordJohnsonSort(vec);
		gettimeofday(&end, NULL);
		double timeVec = getElapsedTime(start, end);

		gettimeofday(&start, NULL);
		PmergeMe::fordJohnsonSort(deq);
		gettimeofday(&end, NULL);
		double timeDeq = getElapsedTime(start, end);

		PmergeMe::printContainer(vec, "After:  ");

		std::cout << "Time to process a range of " << vec.size()
					<< " elements with std::vector : " << timeVec << " us" << std::endl;
		std::cout << "Time to process a range of " << deq.size()
					<< " elements with std::deque  : " << timeDeq << " us" << std::endl;

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}
