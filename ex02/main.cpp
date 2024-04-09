/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:34:48 by gasouza           #+#    #+#             */
/*   Updated: 2024/04/09 01:01:26 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include <exception>
#include <vector>

#include "PmergeMe.hpp"

int argToInt(const char *arg);

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        std::cout << "usage: PmergeMe <numbers...>" << std::endl;
        return 1;
    }

    int inputCount = argc - 1;
    std::vector<int> vecInput(inputCount);

    try{
        for(int i = 0; i < inputCount; i++) {
            vecInput[i] = argToInt(argv[i + 1]);
        }
    } catch(std::exception & e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    PmergeMe::execute(vecInput);

    return 0;
}

int argToInt(const char *arg)
{
    for(size_t i = 0; arg[i]; i++) {
        if (!std::isdigit(arg[i])) {
            throw std::runtime_error("invalid input: " + std::string(arg));
        }
    }
    int value = atoi(arg);
    if (value < 0) {
        throw std::runtime_error("invalid input: " +  std::string(arg));
    }
    return value;
}