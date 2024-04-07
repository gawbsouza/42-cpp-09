/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BtcRepository.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:56:25 by gasouza           #+#    #+#             */
/*   Updated: 2024/03/31 17:03:18 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_REPOSITORY_H
# define BTC_REPOSITORY_H

# include <string>
# include <map>
# include <exception>

typedef struct dataEntry {
    double      value;
    std::string previous;
};

class BtcRepository
{
    
private:
   
   static const std::string         DEFAULT_DATA_FILE;
   static const std::string         DATA_DELEMITER;
   
   std::string                      _dataFile;
   std::map<std::string, double>    _data;

   void loadDataFromDataFile( void );
   
public:

    BtcRepository( void );
    BtcRepository( const std::string & dataFile );
    BtcRepository( const BtcRepository & ref );
    ~BtcRepository( void );

    BtcRepository & operator=( const BtcRepository & ref );
    
    double getAmount( const std::string & date );

    class DataFileNotFoundException: public std::exception
    {
        public:
            virtual const char * what( void ) const  throw();
    };
    
};

#endif