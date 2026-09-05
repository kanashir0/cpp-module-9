/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:24:24 by naharumi          #+#    #+#             */
/*   Updated: 2026/09/05 14:37:04 by gyasuhir         ###   ########.fr       */
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

std::vector<size_t>	generateInsertionSeq(size_t n);
int					jacobsthal(int num);

template <typename Container>
int	blockKey(const Container& c, size_t block, size_t size) {
	return c[block * size + size - 1];
}

template <typename Container>
void	swapBlocks(Container& c, size_t a, size_t b, size_t size) {
	for (size_t i = 0; i < size; i++)
		std::swap(c[a * size + i], c[b * size + i]);
}

template <typename Container>
class BlockLess {
	private:
		const Container*	_c;
		size_t				_size;

	public:
		BlockLess(const Container& c, size_t size) : _c(&c), _size(size) {}

		bool	operator()(int lhs, int rhs) const {
			return blockKey(*_c, static_cast<size_t>(lhs), _size)
				 < blockKey(*_c, static_cast<size_t>(rhs), _size);
		}
};

template <typename Container>
Container	mergeInsertBlocks(Container input, size_t size) {
	size_t	blocks = input.size() / size;
	if (blocks < 2)
		return input;

	bool	hasLeftover = (blocks % 2 == 1);
	size_t	pairs = blocks / 2;

	for (size_t i = 0; i < pairs; i++) {
		if (blockKey(input, 2 * i, size) > blockKey(input, 2 * i + 1, size))
			swapBlocks(input, 2 * i, 2 * i + 1, size);
	}

	input = mergeInsertBlocks(input, size * 2);

	BlockLess<Container>	less(input, size);
	Container				chain;

	chain.push_back(0);
	for (size_t i = 0; i < pairs; i++)
		chain.push_back(static_cast<int>(2 * i + 1));

	size_t				pendCount = pairs + (hasLeftover ? 1 : 0);
	std::vector<size_t>	order = generateInsertionSeq(pendCount);

	for (size_t i = 0; i < order.size(); i++) {
		size_t	k = order[i];
		if (k == 1)
			continue;

		int								pendBlock;
		typename Container::iterator	limit;

		if (hasLeftover && k == pendCount) {
			pendBlock = static_cast<int>(blocks - 1);
			limit = chain.end();
		} else {
			pendBlock = static_cast<int>(2 * (k - 1));
			limit = std::find(chain.begin(), chain.end(),
				static_cast<int>(2 * k - 1));
		}

		typename Container::iterator pos =
			std::lower_bound(chain.begin(), limit, pendBlock, less);
		chain.insert(pos, pendBlock);
	}

	Container	output;
	for (typename Container::const_iterator it = chain.begin(); it != chain.end(); ++it) {
		size_t	base = static_cast<size_t>(*it) * size;
		for (size_t i = 0; i < size; i++)
			output.push_back(input[base + i]);
	}
	for (size_t i = blocks * size; i < input.size(); i++)
		output.push_back(input[i]);

	return output;
}

template <typename Container>
Container	insertMergeSort(Container input) {
	return mergeInsertBlocks(input, 1);
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
