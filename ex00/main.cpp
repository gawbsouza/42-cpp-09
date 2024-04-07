/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:43:49 by gasouza           #+#    #+#             */
/*   Updated: 2024/04/07 20:09:03 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "usage: btc <inputfile>" << std::endl;
        return 1;
    }

    std::string inputFile(argv[1]);

    try {
        
        BitcoinExchange btc;
        btc.run(inputFile);
        
    } catch (std::exception & e) {
        
        std::cout << e.what() << std::endl;
        return 1;
        
    }

    return 0;
}