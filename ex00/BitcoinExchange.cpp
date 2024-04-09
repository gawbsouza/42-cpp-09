/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:25:47 by gasouza           #+#    #+#             */
/*   Updated: 2024/04/09 03:17:31 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <exception>

// -- Constants

const std::string BitcoinExchange::DATA_FILE_NAME = "data.csv";
const std::string BitcoinExchange::DATA_FILE_DELEMITER = ",";
const std::string BitcoinExchange::INPUT_FILE_DELEMITER = "|";
const double BitcoinExchange::INPUT_MIN_VALUE = 0;
const double BitcoinExchange::INPUT_MAX_VALUE = 1000;

// -- Helpers functions header

void removeSpaces(std::string & str);
bool isValidDate(BtcDate & date);
BtcDate parseDateStr(std::string & str);
double parseNumberStr(std::string & str);
double findOnMap(BtcDate & date, std::map<BtcDate, double> & mapref);

// --- BtcDate Struct

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

// --- BitcoinExchange class

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
        throw std::runtime_error("Error when opening [database] file: " + DATA_FILE_NAME);
    }
    
    std::string line;
    
    for(size_t lineCount = 1; std::getline(file, line) ; lineCount++)
    {
        removeSpaces(line);
        if (lineCount == 1 && line.compare("date,exchange_rate") == 0) {
            continue;
        }

        if (line.size() == 0) {
            continue;
        }

        size_t delemiterPos = line.find(DATA_FILE_DELEMITER);

        if (delemiterPos == std::string::npos) {
            std::cout << "[database] file Error on line: " << lineCount << " => invalid line format" << std::endl;
            continue;
        }

        std::string dateStr = line.substr(0, delemiterPos);
        std::string valueStr = line.substr(delemiterPos + 1);

        BtcDate date;
        try {
            date = parseDateStr(dateStr);
            if (!isValidDate(date)) {
                std::cout << "[database] file Error on line: " << lineCount << " => invalid date value" << std::endl;
                continue;
            }
        } catch(std::exception & e) {
            std::cout << "[database] file Error on line: " << lineCount << " => invalid date format" << std::endl;
            continue;
        }

        double value;
        try {
            value = parseNumberStr(valueStr);
        } catch(std::exception & e) {
            std::cout << "[database] file Error on line: " << lineCount << " => invalid value format" << std::endl;
            continue;
        }

        this->_data[date] = value;
    }

    file.close();
}

void BitcoinExchange::run( const std::string & inputFile )
{
    std::ifstream file(inputFile.c_str());
    
    if(!file.is_open()) {
        throw std::runtime_error("Error when opening [input] file: " + inputFile);
    }
    
    std::string line;

    for(size_t lineCount = 1; std::getline(file, line) ; lineCount++)
    {
        removeSpaces(line);
        if (lineCount == 1 && line.compare("date|value") == 0) {
            continue;
        }

        if (line.size() == 0) {
            continue;
        }

        size_t delemiterPos = line.find(INPUT_FILE_DELEMITER);

        if (delemiterPos == std::string::npos) {
            std::cout << "[input] file Error on line: " << lineCount << " => invalid line format" << std::endl;
            continue;
        }

        std::string dateStr = line.substr(0, delemiterPos);
        std::string amountStr = line.substr(delemiterPos + 1);

        BtcDate date;
        try {
            date = parseDateStr(dateStr);
            if (!isValidDate(date)) {
                std::cout << "[input] file Error on line: " << lineCount << " => invalid date value" << std::endl;
                continue;
            }
        } catch(std::exception & e) {
            std::cout << "[input] file Error on line: " << lineCount << " => invalid date format" << std::endl;
            continue;
        }

        double amount;
        try {
            amount = parseNumberStr(amountStr);
        } catch(std::exception & e) {
            std::cout << "[input] file Error on line: " << lineCount << " => invalid amount format" << std::endl;
            continue;
        }

        if (amount < INPUT_MIN_VALUE) {
            std::cout << "[input] file Error on line: " << lineCount << " => amount is less than minimum allowed" << std::endl;
            continue;
        }

        if (amount > INPUT_MAX_VALUE) {
            std::cout << "[input] file Error on line: " << lineCount << " => amount is greater than maximum allowed" << std::endl;
            continue;
        }
        
        double value;
  
        try {
            value = findOnMap(date, this->_data) * amount;
        } catch (std::exception & e) {
            std::cout << "[input] file Error on line: " << lineCount << " => " << e.what() << std::endl;
			continue;
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
    int monthDays[12] = {
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
    if (!stream.eof() || str.size() == 0) {
        throw std::invalid_argument("invalid format");
    }

    return number;
}

double findOnMap(BtcDate & date, std::map<BtcDate, double> & mapref)
{
    std::map<BtcDate, double>::iterator foundAt;

    foundAt = mapref.upper_bound(date);

    if (foundAt == mapref.end() || (foundAt->first != date && foundAt == mapref.begin())) { 
        throw std::runtime_error("no value available for date");
    }

    if (foundAt->first != date) { foundAt--; }

    return foundAt->second;
}