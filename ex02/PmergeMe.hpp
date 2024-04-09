/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:52:40 by gasouza           #+#    #+#             */
/*   Updated: 2024/04/09 00:38:13 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_MERGE_ME_H
# define P_MERGE_ME_H

#include <vector>
#include <deque>

class PmergeMe
{

public:
    
    static void execute( const std::vector<int> & ref );
    
private:
    
    PmergeMe( void );
    ~PmergeMe( void );

    template <typename T>
    static void _mergeInsertion(T & ref);

    template <typename T>
    static void _insertionSort( T & vec );

    template <typename T>
    static void _merge( T & left, T & right, T & ref);

};

#endif
