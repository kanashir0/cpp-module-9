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
#include <string>
#include <iostream>
#include <cstddef>

/*
** Ford-Johnson (merge-insertion sort).
**
** O algoritmo trabalha sobre "blocos" de tamanho s de elementos consecutivos.
** Invariante mantida em todos os niveis: o ULTIMO elemento de um bloco e o
** maior valor daquele bloco. Esse elemento e a chave do bloco.
**
** A cada nivel os blocos sao emparelhados (1 comparacao por par) e o par e
** arrumado de modo que o bloco de maior chave fique em segundo. Assim os dois
** blocos de um par ficam FISICAMENTE ADJACENTES, e a recursao sobre blocos de
** tamanho 2s reordena o par inteiro como uma unidade: o bloco menor viaja
** colado ao seu parceiro maior. E isso que preserva a associacao par<->parceiro
** exigida pelo Ford-Johnson e que permite limitar cada busca binaria.
*/
class PmergeMe {
	private:
		static size_t jacobsthal(size_t k);

		template <typename Container>
		static int blockKey(const Container& arr, size_t block, size_t s);
		template <typename Container>
		static void swapBlocks(Container& arr, size_t a, size_t b, size_t s);
		template <typename Container>
		static void sortBlocks(Container& arr, size_t s);

		/* Compara dois blocos (identificados pelo indice) pela chave. */
		template <typename Container>
		class BlockLess {
			private:
				const Container*	_arr;
				size_t				_s;
			public:
				BlockLess(const Container& arr, size_t s) : _arr(&arr), _s(s) {}
				bool operator()(int lhs, int rhs) const {
					return ((*_arr)[static_cast<size_t>(lhs) * _s + _s - 1]
						< (*_arr)[static_cast<size_t>(rhs) * _s + _s - 1]);
				}
		};
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
int PmergeMe::blockKey(const Container& arr, size_t block, size_t s) {
	return (arr[block * s + s - 1]);
}

template <typename Container>
void PmergeMe::swapBlocks(Container& arr, size_t a, size_t b, size_t s) {
	for (size_t k = 0; k < s; ++k)
		std::swap(arr[a * s + k], arr[b * s + k]);
}

template <typename Container>
void PmergeMe::sortBlocks(Container& arr, size_t s) {
	size_t n = arr.size() / s;
	if (n < 2)
		return ;

	bool	isOdd = (n % 2 != 0);
	size_t	pairs = n / 2;

	/* 1) Uma comparacao por par: o bloco de maior chave fica em segundo. */
	for (size_t i = 0; i < pairs; ++i) {
		if (blockKey(arr, 2 * i, s) > blockKey(arr, 2 * i + 1, s))
			swapBlocks(arr, 2 * i, 2 * i + 1, s);
	}

	/* 2) Ordena recursivamente os pares como blocos de tamanho 2s.
	**    O parceiro menor viaja junto porque esta colado ao maior. */
	sortBlocks(arr, 2 * s);

	/* 3) Merge-insertion. Depois da recursao, o bloco 2k e o menor do par k
	**    e o bloco 2k+1 e o maior; os pares estao ordenados entre si.
	**    Cadeia principal: [ b1, a1, a2, ..., ak ]  com b1 = bloco 0. */
	BlockLess<Container>	less(arr, s);
	Container				main;

	main.push_back(0);
	for (size_t i = 0; i < pairs; ++i)
		main.push_back(static_cast<int>(2 * i + 1));

	/* Insere os pendentes b2..bk na ordem de Jacobsthal: b3 b2, b5 b4,
	** b11 b10 ... b6, ... Cada bj entra por busca binaria limitada a
	** posicao do seu parceiro aj, pois sabemos que bj < aj.
	**
	** O bloco impar sobrando (sem parceiro) entra na lista de pendentes como
	** ultimo elemento e e inserido tambem na ordem de Jacobsthal, so que sem
	** limite superior. Inseri-lo aqui em vez de no fim de tudo e o que fecha
	** a contagem otima de comparacoes. */
	size_t pendCount = pairs + (isOdd ? 1 : 0);
	size_t prev = 1;
	for (size_t k = 3; prev < pendCount; ++k) {
		size_t curr = jacobsthal(k);
		if (curr > pendCount)
			curr = pendCount;
		for (size_t j = curr; j > prev; --j) {
			int								pendBlock;
			typename Container::iterator	limit;

			if (isOdd && j == pendCount) {
				pendBlock = static_cast<int>(n - 1);
				limit = main.end();
			} else {
				pendBlock = static_cast<int>(2 * (j - 1));
				limit = std::find(main.begin(), main.end(),
					static_cast<int>(2 * j - 1));
			}
			typename Container::iterator pos =
				std::lower_bound(main.begin(), limit, pendBlock, less);
			main.insert(pos, pendBlock);
		}
		prev = curr;
	}

	/* 4) Reescreve os n*s primeiros elementos na ordem dos blocos da cadeia.
	**    O resto (menos de s elementos) pertence ao nivel de cima e fica. */
	Container	sorted;
	for (typename Container::const_iterator it = main.begin(); it != main.end(); ++it) {
		size_t base = static_cast<size_t>(*it) * s;
		for (size_t k = 0; k < s; ++k)
			sorted.push_back(arr[base + k]);
	}
	for (size_t i = 0; i < sorted.size(); ++i)
		arr[i] = sorted[i];
}

template <typename Container>
void PmergeMe::fordJohnsonSort(Container& arr) {
	sortBlocks(arr, 1);
}
