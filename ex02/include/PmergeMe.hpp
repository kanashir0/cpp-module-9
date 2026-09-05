/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:54:42 by joaolive          #+#    #+#             */
/*   Updated: 2026/03/09 10:38:20 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

class PmergeMe {
	private:
		static void genJacobsthal(std::vector<int>& seq, int n);

		template <typename Container>
		static void createChains(Container& arr, Container& mainChain, Container& pend, int& straggler, bool& hasStraggler);
		template <typename Container>
		static void insertPend(Container& mainChain, Container& pend, int straggler, bool hasStraggler);
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		template <typename Container>
		static void fordJohnsonSort(Container& arr);
		template <typename Container>
		static void printContainer(const Container& arr, const std::string& prefix);
};

template <typename Container>
void PmergeMe::printContainer(const Container& arr, const std::string& prefix) {
	std::cout << prefix;
	typename Container::const_iterator it = arr.begin();
	size_t count = 0;

	for (; it != arr.end(); ++it, ++count) {
		std::cout << *it << " ";
		if (count == 4 && arr.size() > 5) {
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl;
}

template <typename Container>
void PmergeMe::createChains(Container& arr, Container& mainChain, Container& pend, int& straggler, bool& hasStraggler) {
	if (arr.size() % 2 != 0) {
		straggler = arr.back();
		hasStraggler = true;
		arr.pop_back();
	}

	for (size_t i = 0; i < arr.size(); i += 2) {
		if (arr[i] > arr[i + 1]) {
			mainChain.push_back(arr[i]);
			pend.push_back(arr[i + 1]);
		} else {
			mainChain.push_back(arr[i + 1]);
			pend.push_back(arr[i]);
		}
	}
}

template <typename Container>
void PmergeMe::insertPend(Container& mainChain, Container& pend, int straggler, bool hasStraggler) {
	std::vector<int> jacobSeq;
	genJacobsthal(jacobSeq, pend.size());

	if (!pend.empty()) {
		mainChain.insert(mainChain.begin(), pend[0]);
	}

	size_t lastPos = 1;
	for (size_t i = 1; i < jacobSeq.size(); ++i) {
		size_t currentPos = jacobSeq[i];
		if (currentPos > pend.size()) {
			currentPos = pend.size();
		}

		for (size_t j = currentPos; j > lastPos; --j) {
			int valueToInsert = pend[j - 1];
			typename Container::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), valueToInsert);
			mainChain.insert(it, valueToInsert);
		}
		lastPos = currentPos;
	}

	if (hasStraggler) {
		typename Container::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(it, straggler);
	}
}

template <typename Container>
void PmergeMe::fordJohnsonSort(Container& arr) {
	if (arr.size() < 2)
		return;

	Container mainChain;
	Container pend;
	int straggler = -1;
	bool hasStraggler = false;

	createChains(arr, mainChain, pend, straggler, hasStraggler);
	fordJohnsonSort(mainChain);
	insertPend(mainChain, pend, straggler, hasStraggler);

	arr = mainChain;
}
