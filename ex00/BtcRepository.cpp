/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BtcRepository.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:06:41 by gasouza           #+#    #+#             */
/*   Updated: 2024/03/31 16:55:58 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BtcRepository.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>

const std::string BtcRepository::DEFAULT_DATA_FILE    = "data.csv";
const std::string BtcRepository::DATA_DELEMITER       = ",";

BtcRepository::BtcRepository( void ): _dataFile(DEFAULT_DATA_FILE)
{
    loadDataFromDataFile();
}

BtcRepository::BtcRepository( const std::string & dataFile ): _dataFile(dataFile)
{
    loadDataFromDataFile();
}

BtcRepository::BtcRepository( const BtcRepository & ref )
{
    *this = ref;
}

BtcRepository::~BtcRepository( void )
{
    this->_data.clear();
}

BtcRepository &BtcRepository::operator=( const BtcRepository & ref )
{
    if (this != &ref) {
        this->_dataFile = ref._dataFile;
        this->_data = ref._data;
    }
    return *this;
}

void BtcRepository::loadDataFromDataFile( void )
{
    std::ifstream file(this->_dataFile.c_str());
    
    if(!file.is_open()) {
        std::cout << "Error when readind data file: " << this->_dataFile << std::endl;
    }
    
    std::string line;
    std::string date;
    std::string value;
    size_t delemiterPos;
    
    while(std::getline(file, line))
    {
        delemiterPos = line.find(DATA_DELEMITER);
        
        date = line.substr(0, delemiterPos);
        value = line.substr(delemiterPos + 1);
        
        this->_data[date] = atof(value.c_str());
    }

    file.close();
}

double BtcRepository::getAmount( const std::string & date )
{
    return this->_data[date];
}

const char *BtcRepository::DataFileNotFoundException::what( void ) const throw()
{
    return "Data file not found";
}