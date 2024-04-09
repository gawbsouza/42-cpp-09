/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:52:42 by gasouza           #+#    #+#             */
/*   Updated: 2024/04/09 01:02:48 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <iostream>

PmergeMe::PmergeMe( void ) {}
PmergeMe::~PmergeMe( void ) {}

template <typename T>
void PmergeMe::_mergeInsertion(T & ref)
{
    size_t size = ref.size();

    if (size <= 100) {
        PmergeMe:: _insertionSort(ref);
        return;
    }

    size_t leftBranchSize = size / 2;
    size_t rightBranchSize = size - leftBranchSize;

    T leftBranch(leftBranchSize);
    T rightBranch(rightBranchSize);

    for(size_t i = 0; i < leftBranchSize; i++) { leftBranch[i] = ref[i]; }
    for(size_t i = leftBranchSize; i < size; i++) { rightBranch[i - leftBranchSize] = ref[i]; }

    PmergeMe::_mergeInsertion(leftBranch);
    PmergeMe::_mergeInsertion(rightBranch);
    PmergeMe::_merge(leftBranch, rightBranch, ref);
}

template <typename T>
void printValues( const T & vals)
{
    for (size_t i = 0; i < vals.size(); i++) {
        std::cout << vals[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::execute( const std::vector<int> & ref)
{
    std::vector<int> vec(ref.size());
    std::deque<int> deq(ref.size());

    for(size_t i = 0; i < ref.size(); i++) { vec[i] = ref[i]; deq[i] = ref[i];}

    std::cout << "Before: "; printValues(vec);

    clock_t vecStart = clock();
    PmergeMe::_mergeInsertion(vec);
    clock_t vecEnd = clock();

    clock_t deqStart = clock();
    PmergeMe::_mergeInsertion(deq);
    clock_t deqEnd = clock();

    double vecTime = static_cast<double>( vecEnd - vecStart ) / CLOCKS_PER_SEC;
    double deqTime = static_cast<double>( deqEnd - deqStart ) / CLOCKS_PER_SEC;

    std::cout << "After:  "; printValues(vec);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << std::fixed << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque:  " << std::fixed << deqTime << " us" << std::endl;
}

template <typename T>
void PmergeMe::_insertionSort( T & ref )
{
    if (ref.size() < 2) return;
    for(size_t i = 1; i < ref.size(); i++)
    {
        int tmp = ref[i];
        int backIndex = i - 1;
        for(; backIndex >= 0 && ref[backIndex] > tmp; backIndex--) {
            ref[backIndex + 1] = ref[backIndex];
        }
        ref[backIndex + 1] = tmp;
    }
}

template <typename T>
void PmergeMe::_merge( T & left, T & right, T & ref)
{
    size_t leftBranchSize = ref.size() / 2;
    size_t rightBranchSize = ref.size() - leftBranchSize;
    size_t i = 0, l = 0, r = 0;

    while (l < leftBranchSize && r < rightBranchSize) {
        if (left[l] < right[r]) {
            ref[i] = left[l]; i++; l++; continue ;
        }
        ref[i] = right[r]; i++; r++;
    }
    
    while(l < leftBranchSize) { ref[i] = left[l]; i++; l++; }
    while(r < rightBranchSize) { ref[i] = right[r]; i++; r++; }
}
