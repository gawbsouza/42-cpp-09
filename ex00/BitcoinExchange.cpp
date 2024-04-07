/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:25:47 by gasouza           #+#    #+#             */
/*   Updated: 2024/03/31 18:39:53 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>

const std::string BitcoinExchange::DATA_FILE = "data.csv";
const std::string BitcoinExchange::DATA_FILE_DELEMITER = ",";
const std::string BitcoinExchange::INPUT_FILE_DELEMITER = " | ";
const double BitcoinExchange::INPUT_VALUE_MIN_LIMIT = 0;
const double BitcoinExchange::INPUT_VALUE_MAX_LIMIT = 1000;

BitcoinExchange::BitcoinExchange( void )
{
    loadData();
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & ref )
{
    *this = ref;
}

BitcoinExchange::~BitcoinExchange()
{
    this->_data.clear();
}

BitcoinExchange & BitcoinExchange::operator=( const BitcoinExchange & ref )
{
    if (this != &ref) {
        this->_data.clear();
        this->_data = ref._data;
    }
    return *this;
}


void BitcoinExchange::loadData( void )
{
    std::ifstream file(DATA_FILE.c_str());
    
    if(!file.is_open()) {
        std::cout << "Error when reading data.csv file " << std::endl;
    }
    
    std::string line;
    std::string date;
    std::string value;
    size_t delemiterPos;
    
    while(std::getline(file, line))
    {
        delemiterPos = line.find(DATA_FILE_DELEMITER);
        date = line.substr(0, delemiterPos);
        value = line.substr(delemiterPos + 1);
        this->_data[date] = atof(value.c_str());
    }

    file.close();
}

bool BitcoinExchange::isValidDate( const std::string & date )
{
    std::string year;
    std::string month;
    std::string day;

    size_t yearAt = date.find("-");
    size_t monthAt = date.find("-", yearAt + 1);
    // size_t dayAt = date.find("-", monthAt + 1);

    if (
        yearAt  == std::string::npos ||
        monthAt == std::string::npos
        // dayAt   == std::string::npos
    ){
        std::cout << "Error: bad date value => " << date << std::endl;
        return false;
    }

    year = date.substr(0, yearAt);
    month = date.substr(yearAt + 1, monthAt);
    day = date.substr(monthAt + 1);

    int yearInt = atoi(year.c_str());
    int monthInt = atoi(month.c_str());
    int dayInt = atoi(day.c_str());
    
    if (
        (yearInt < 2000 || yearInt > 2050) ||
        (monthInt < 1   || monthInt > 12)  ||
        (dayInt < 1     || dayInt > 31)
    ){
        std::cout << "Error: bad date value => " << date << std::endl;
        return false;
    }

    return true;
}

bool BitcoinExchange::isValidAmount( const std::string & amount )
{

    double amountDouble = atof(amount.c_str());
    
    if (amountDouble < INPUT_VALUE_MIN_LIMIT) {
        std::cout 
            << "Error: number must be grater than " 
            << INPUT_VALUE_MIN_LIMIT << " => " << amount << std::endl;
        return false;
    }
    
    if (amountDouble > INPUT_VALUE_MAX_LIMIT) {
        std::cout 
            << "Error: number must be less than " 
            << INPUT_VALUE_MAX_LIMIT << " => " << amount << std::endl;
        return false;
    }

    return true;
}

void BitcoinExchange::printExchange( const std::string date, double exchange )
{
    std::cout << date << " : " << exchange << std::endl;
}

void BitcoinExchange::findAmounts( const std::string & inputFile )
{
    std::ifstream file(inputFile.c_str());
    
    if(!file.is_open()) {
        std::cout << "Error when reading file: " << file << std::endl;
        return;
    }
    
    std::string line;

    while(std::getline(file, line))
    {
        size_t delemiterPos = line.find(INPUT_FILE_DELEMITER);
        if (delemiterPos == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        
        if (line.compare("date | value") == 0) continue;
        
        std::string date = line.substr(0, delemiterPos);
        std::string amount = line.substr(delemiterPos + INPUT_FILE_DELEMITER.size());
        
        if (!this->isValidDate(date)) continue;
        if (!this->isValidAmount(amount)) continue;

        double amountDouble = atof(amount.c_str());
        
        this->printExchange(date, amountDouble);
    }

    file.close();
}
