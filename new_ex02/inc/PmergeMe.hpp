/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:24:24 by naharumi          #+#    #+#             */
/*   Updated: 2025/07/31 15:54:54 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <deque>
#include <set>

class PmergeMe {
	private:
		std::vector<int>	_vec;
		std::deque<int>		_deq;
		
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& other);
		~PmergeMe(void);
		
		PmergeMe&	operator=(const PmergeMe& other);
		
		void	processInput(int ac, char **av);
		void	sortVector(void);
		void	sortDeque(void);
};

std::vector<int>	generateInsertionSeq(size_t n);
int	jacobsthal(int num);

template <typename Container>
void	binaryInsert(Container& sorted, Container& pend) {
	std::vector<int>	insertionSeq = generateInsertionSeq(pend.size());

	for (size_t i = 0; i < insertionSeq.size(); i++) {
		size_t index = insertionSeq[i] - 1;
		if (index >= pend.size())
			continue;
			
		int	elem = pend[index];
		typename Container::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), elem);
		sorted.insert(pos, elem);
	}
}

template <typename Container>
Container	insertMergeSort(Container input) {
	if (input.size() <= 1)
		return input;

	int	leftoverElem = -1;
	if (input.size() % 2 == 1) {
		leftoverElem = input.back();
		input.pop_back();
	}
	
	Container	smaller, larger;
	for (size_t i = 0; i < input.size(); i += 2) {
		int	first = input[i];
		int	second = input[i + 1];
		if (first > second)
			std::swap(first, second);
		smaller.push_back(first);
		larger.push_back(second);
	}
	if (leftoverElem != -1)
		smaller.push_back(leftoverElem);

	Container	sorted = insertMergeSort<Container>(larger);
	binaryInsert(sorted, smaller);
	return sorted;
}

template <typename Container>
bool	isSorted(const Container& c) {
	if (c.size() < 2)
		return true;

	typename Container::const_iterator it = c.begin();
	typename Container::const_iterator next = it;
	++next;

	while (next != c.end()) {
		if (*it > *next)
			return false;
		++it;
		++next;
	}
	return true;
}

template <typename Container>
void	printContainer(const Container& c) {
	typename Container::const_iterator	it = c.begin();

	while (it != c.end()) {
		std::cout << " " << *it ;
		++it;
	}
	std::cout << std::endl; 
}

#endif
