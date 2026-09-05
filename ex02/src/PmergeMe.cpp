/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:24:41 by naharumi          #+#    #+#             */
/*   Updated: 2026/09/05 14:37:41 by gyasuhir         ###   ########.fr       */
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
	for (int i = 1; i < ac; i++) {
		std::string	input = av[i];
		std::istringstream	iss(input);
		int	value;

		iss >> value;
		if (iss.fail() || !iss.eof() || value <= 0)
			throw std::invalid_argument("invalid input: " + input);

		_vec.push_back(value);
		_deq.push_back(value);
	}

	std::vector<int>	check = _vec;
	std::sort(check.begin(), check.end());

	std::vector<int>::iterator	dup = std::adjacent_find(check.begin(), check.end());
	if (dup != check.end()) {
		std::ostringstream	oss;
		oss << "duplicated input: " << *dup;
		throw std::invalid_argument(oss.str());
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

std::vector<size_t>	generateInsertionSeq(size_t n) {
	std::vector<size_t>	seq;
	size_t				prev = 0;

	for (int j = 2; prev < n; j++) {
		size_t	curr = static_cast<size_t>(jacobsthal(j));
		if (curr > n)
			curr = n;

		for (size_t k = curr; k > prev; k--)
			seq.push_back(k);
		prev = curr;
	}
	return seq;
}

int	jacobsthal(int num) {
	if (num <= 0)
		return 0;

	int	prev = 0;
	int	curr = 1;

	for (int i = 1; i < num; i++) {
		int	next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	return curr;
}
