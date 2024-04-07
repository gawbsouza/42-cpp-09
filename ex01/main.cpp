/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:17:14 by gasouza           #+#    #+#             */
/*   Updated: 2024/04/07 22:35:41 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "usage: RPN <expression>" << std::endl;
        return 1;
    }

    std::string expression(argv[1]);
    double result;

    try {
        result = RPN::calcule(expression);
    } catch(std::exception & e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << result << std::endl;
    
    return 0;
}