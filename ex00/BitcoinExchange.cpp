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
#include <algorithm>
#include <sstream>

const std::string BitcoinExchange::DATA_FILE_NAME = "data.csv";
const std::string BitcoinExchange::DATA_FILE_DELEMITER = ",";
const std::string BitcoinExchange::INPUT_FILE_DELEMITER = " | ";
const double BitcoinExchange::INPUT_MIN_VALUE = 0;
const double BitcoinExchange::INPUT_MAX_VALUE = 1000;

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
    std::ifstream file(DATA_FILE_NAME.c_str());
    
    if(!file.is_open()) {
        throw std::runtime_error("error when opening datebase file:" + DATA_FILE_NAME);
    }
    
    size_t linecount = 0;
    std::string line;
    
    while(std::getline(file, line))
    {
        removeSpaces(line);
        size_t delemiterPos = line.find(DATA_FILE_DELEMITER);

        if (delemiterPos == std::string::npos) {
            std::cout << "[database file] line: " << linecount << " => invalid line format: " << line << std::endl;
            continue;
        }

        std::string dateStr = line.substr(0, delemiterPos);
        std::string valueStr = line.substr(delemiterPos + 1);

        btcdate date;
        try {
            date = parseDateStr(dateStr);
        } catch(std::exception & e) {
            std::cout << "[database file] line: " << linecount << " => invalid date format: " << line << std::endl;
            continue;
        }

        double value;
        try {
            value = parseNumberStr(valueStr);
        } catch(std::exception & e) {
            std::cout << "[database file] line: " << linecount << " => invalid value format: " << line << std::endl;
            continue;
        }

        this->_data[date] = value;
        ++linecount;
    }

    file.close();
}

void removeSpaces(std::string & str) 
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}

bool isValidDate(btcdate & date)
{
    int monthDays[12] {
        31, //jan
        28, //feb
        31, //mar
        30, //apr
        31, //may
        30, //jun
        31, //jul
        31, //aug
        30, //sep
        31, //oct
        30, //nov
        31  //dec
    };

    if (date.year <= 0 || date.month <= 0  || date.day <= 0) { return false; }
    if (date.month > 12) { return false; }
    if (date.day > monthDays[date.month - 1]){ return false; }

    return true;
}

btcdate parseDateStr(std::string & str)
{
    btcdate d;
    char del[2];
    char delemiter = '-';
    std::istringstream stream(str);

    stream >> d.year >> del[0] >> d.month >> del[1] >> d.day;

    if (del[0] != delemiter || del[1] != delemiter || !stream.eof()) {
        throw std::invalid_argument("invalid format");
    }

    return d;
}

double parseNumberStr(std::string & str)
{
    std::istringstream stream(str);
    double number;

    stream >> number;
    if (!stream.eof()) {
        throw std::invalid_argument("invalid format");
    }

    return number;
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
    
    if (amountDouble < INPUT_MIN_VALUE) {
        std::cout 
            << "Error: number must be grater than " 
            << INPUT_MIN_VALUE << " => " << amount << std::endl;
        return false;
    }
    
    if (amountDouble > INPUT_MAX_VALUE) {
        std::cout 
            << "Error: number must be less than " 
            << INPUT_MAX_VALUE << " => " << amount << std::endl;
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
