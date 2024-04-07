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
#include <exception>

const std::string BitcoinExchange::DATA_FILE_NAME = "data.csv";
const std::string BitcoinExchange::DATA_FILE_DELEMITER = ",";
const std::string BitcoinExchange::INPUT_FILE_DELEMITER = "|";
const double BitcoinExchange::INPUT_MIN_VALUE = 0;
const double BitcoinExchange::INPUT_MAX_VALUE = 1000;

bool BtcDate::operator<(const BtcDate &ref) const {
    if (year != ref.year) return year < ref.year;
    if (month != ref.month) return month < ref.month;
    return day < ref.day;
}

bool BtcDate::operator>(const BtcDate &ref) const {
    if (year != ref.year) return year > ref.year;
    if (month != ref.month) return month > ref.month;
    return day > ref.day;
}

bool BtcDate::operator==(const BtcDate &ref) const {
    return year == ref.year && month == ref.month && day == ref.day;
}

bool BtcDate::operator!=(const BtcDate &ref) const {
    return year != ref.year || month != ref.month || day != ref.day;
}

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
    
    size_t lineCount = 0;
    std::string line;
    
    while(std::getline(file, line))
    {
        removeSpaces(line);
        size_t delemiterPos = line.find(DATA_FILE_DELEMITER);

        if (delemiterPos == std::string::npos) {
            std::cout << "[database file] line: " << lineCount << " => invalid line format: " << line << std::endl;
            continue;
        }

        std::string dateStr = line.substr(0, delemiterPos);
        std::string valueStr = line.substr(delemiterPos + 1);

        BtcDate date;
        try {
            date = parseDateStr(dateStr);
        } catch(std::exception & e) {
            std::cout << "[database file] line: " << lineCount << " => invalid date format: " << line << std::endl;
            continue;
        }

        double value;
        try {
            value = parseNumberStr(valueStr);
        } catch(std::exception & e) {
            std::cout << "[database file] line: " << lineCount << " => invalid value format: " << line << std::endl;
            continue;
        }

        this->_data[date] = value;
        ++lineCount;
    }

    file.close();
}

void BitcoinExchange::run( const std::string & inputFile )
{
    std::ifstream file(inputFile.c_str());
    
    if(!file.is_open()) {
        throw std::runtime_error("error when opening input file: " + inputFile);
    }
    
    size_t lineCount = 0;
    std::string line;

    while(std::getline(file, line))
    {
        removeSpaces(line);
        size_t delemiterPos = line.find(INPUT_FILE_DELEMITER);

        if (delemiterPos == std::string::npos) {
            std::cout << "[input file] line: " << lineCount << " => invalid line format: " << line << std::endl;
            continue;
        }

        std::string dateStr = line.substr(0, delemiterPos);
        std::string amountStr = line.substr(delemiterPos + 1);

        BtcDate date;
        try {
            date = parseDateStr(dateStr);
        } catch(std::exception & e) {
            std::cout << "[input file] line: " << lineCount << " => invalid date format: " << line << std::endl;
            continue;
        }

        double amount;
        try {
            amount = parseNumberStr(amountStr);
        } catch(std::exception & e) {
            std::cout << "[input file] line: " << lineCount << " => invalid amount format: " << line << std::endl;
            continue;
        }

        if (amount < INPUT_MIN_VALUE) {
            std::cout << "[input file] line: " << lineCount << " => amount is less than minimum allowed: " << line << std::endl;
            continue;
        }

        if (amount > INPUT_MAX_VALUE) {
            std::cout << "[input file] line: " << lineCount << " => value is greater than maximum allowed: " << line << std::endl;
            continue;
        }
        
        double value;
  
        try {
            value = findOnMap(date, this->_data) * amount;
        } catch (std::exception & e) {
            std::cout << "[input file] line: " << lineCount << " => " << e.what() << std::endl;
        }

        std::cout << dateStr << " => " << amountStr << " = " << value << std::endl;
    }

    file.close();
}


void removeSpaces(std::string & str) 
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}

bool isValidDate(BtcDate & date)
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

BtcDate parseDateStr(std::string & str)
{
    BtcDate d;
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

double findOnMap(BtcDate & date, std::map<BtcDate, double> & mapref)
{
    std::map<BtcDate, double>::iterator foundAt;

    foundAt = mapref.upper_bound(date);

    if (foundAt == mapref.end() || (foundAt->first != date && foundAt == mapref.begin())) { 
        return 0;
    }

    if (foundAt->first != date) { foundAt--; }

    return foundAt->second;
}