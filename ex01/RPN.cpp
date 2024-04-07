/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:23:00 by gasouza           #+#    #+#             */
/*   Updated: 2024/04/07 22:43:16 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <iostream>
#include <exception>
#include <stdlib.h>

RPN::RPN( void ) {}
RPN::~RPN( void ) {}

bool isOperator( const std::string & ref );
double calc( double v1, double v2, const std::string & op );
bool isValidNumber( const std::string & ref );

double RPN::calcule(const std::string & exp )
{
    std::stack<double> stk;
    std::istringstream stream(exp);
    std::string readed;
    std::string op;

    while(!stream.eof())
    {
        stream >> readed;
        
        if (isOperator(readed)) 
        {
            op = readed;
            if (stk.size() < 2) {
                throw std::invalid_argument("invalid expression");
            }
            double v2 = stk.top(); stk.pop();
            double v1 = stk.top(); stk.pop();
            stk.push(calc(v1, v2, op));
            continue;
        }
        
        if (!isValidNumber(readed)) {
            throw std::invalid_argument("invalid input: " + readed);
        }

        int val = atoi(readed.c_str());
        
        if (val > 9) {
            throw std::invalid_argument("number grater than maximum allowed: " + readed);
        }
        if (val < 0) {
            throw std::invalid_argument("number grater than minimum allowed: " + readed);
        }
        
        stk.push(val);
    }
    
    if (!isOperator(op)) {
        throw std::invalid_argument("invalid expression");
    }
    
    return stk.top();
}

bool isOperator( const std::string & ref )
{
    if (ref.compare("+") == 0) return true;
    if (ref.compare("-") == 0) return true;
    if (ref.compare("*") == 0) return true;
    if (ref.compare("/") == 0) return true;
    return false;
}

bool isValidNumber( const std::string & ref )
{
    if (ref.size() == 0) return false;
    for(size_t i = 0; i < ref.size(); i++) {
        if (!std::isdigit(ref.at(i))) return false;
    }
    return true;
}

double calc( double v1, double v2, const std::string & op )
{
    if (op.compare("+") == 0) return v1 + v2;
    if (op.compare("-") == 0) return v1 - v2;
    if (op.compare("*") == 0) return v1 * v2;
    if (op.compare("/") == 0) return v1 / v2;
    return 0;
}
