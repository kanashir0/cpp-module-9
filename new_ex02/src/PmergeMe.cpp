/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:24:41 by naharumi          #+#    #+#             */
/*   Updated: 2025/07/29 09:24:41 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {
}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe::~PmergeMe(void) {
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

void	PmergeMe::processInput(int ac, char **av) {
	std::set<int>	numbers;

	for (int i = 1; i < ac; i++) {
		std::string	input = av[i];
		std::istringstream	iss(input);
		int	value;

		iss >> value;
		if (iss.fail() || !iss.eof() || value <= 0)
			throw std::invalid_argument("invalid input: " + input);
		if (numbers.count(value) == 1)
			throw std::invalid_argument("duplicated input: " + input);
			
		numbers.insert(value);
		_vec.push_back(value);
		_deq.push_back(value);
	}
}

void	PmergeMe::sortVector(void) {
	std::cout << "Before :";
	printContainer(_vec);

	std::clock_t		start = clock();
	std::vector<int>	sorted = insertMergeSort<std::vector<int> >(_vec);
	std::clock_t		finish = clock();
	
	if (!isSorted<std::vector<int> >(sorted))
		throw std::runtime_error("sorting vector failed");
	
	std::cout << "After  :";
	printContainer(sorted);

	double	elapsedTime = static_cast<double>(finish - start) * 1000000 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : "
			  << std::setprecision(5) << elapsedTime << " us" << std::endl;
}

void	PmergeMe::sortDeque(void) {
	std::clock_t	start = clock();
	std::deque<int>	sorted = insertMergeSort<std::deque<int> >(_deq);
	std::clock_t	finish = clock();
	
	if (!isSorted<std::deque<int> >(sorted))
		throw std::runtime_error("sorting deque failed");

	double	elapsedTime = static_cast<double>(finish - start) * 1000000 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque  : "
			  << std::setprecision(5) << elapsedTime << " us" << std::endl;
}

std::vector<int>	generateInsertionSeq(size_t n) {
	std::vector<int>	seq;
	std::set<int>		seen;

	for (int j = 2; seq.size() < n; ++j) {
		int num = jacobsthal(j);
		if (num > static_cast<int>(n))
			num = static_cast<int>(n);

		while (num > 0 && !seen.count(num)) {
			seq.push_back(num);
			seen.insert(num);
			--num;
		}
	}
	return seq;
}

int	jacobsthal(int num) {
	if (num == 0)
		return 0;
	if (num == 1)
		return 1;
	return jacobsthal(num - 1) + 2 * jacobsthal(num - 2);
}
