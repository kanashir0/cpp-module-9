/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:55:07 by joaolive          #+#    #+#             */
/*   Updated: 2026/03/08 17:21:52 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	(void)other;
	return (*this);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::genJacobsthal(std::vector<int>& seq, int n) {
	if (n <= 0)
		return ;
	seq.push_back(0);
	if (n == 1)
		return ;
	seq.push_back(1);
	int i = 2;
	for (;;) {
		int nextVal = seq[i - 1] + 2 * seq[i - 2];
		seq.push_back(nextVal);
		if (nextVal > n)
			break ;
		i++;
	}
}

