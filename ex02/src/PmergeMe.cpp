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

/*
** k-esimo numero de Jacobsthal: J(0)=0, J(1)=1, J(k)=J(k-1)+2*J(k-2).
** Sequencia: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, ...
**
** Esses numeros dao a ordem otima de insercao dos pendentes: eles caem
** alternadamente logo acima e logo abaixo de potencias de 2, o que faz cada
** busca binaria aproveitar ao maximo as comparacoes que gasta.
*/
size_t PmergeMe::jacobsthal(size_t k) {
	size_t prev = 0;
	size_t curr = 1;

	for (size_t i = 1; i < k; ++i) {
		size_t next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	return (curr);
}
