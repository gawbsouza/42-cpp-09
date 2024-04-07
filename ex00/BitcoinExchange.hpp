/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:21:39 by gasouza           #+#    #+#             */
/*   Updated: 2024/03/31 18:21:25 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_H
# define BITCOIN_EXCHANGE_H

# include <string>
# include <map>

class BitcoinExchange
{
private:

    static const std::string        DATA_FILE;
    static const std::string        DATA_FILE_DELEMITER;
    static const std::string        INPUT_FILE_DELEMITER;
    static const double             INPUT_VALUE_MAX_LIMIT;
    static const double             INPUT_VALUE_MIN_LIMIT;

    std::map<std::string, double>   _data;

    void    loadData( void );
    bool    isValidDate( const std::string & date );
    bool    isValidAmount( const std::string & amount );
    void    printExchange( const std::string date, double exchange );

public:

    BitcoinExchange( void );
    BitcoinExchange( const BitcoinExchange & ref );
    ~BitcoinExchange();

    BitcoinExchange & operator=( const BitcoinExchange & ref );

    void findAmounts( const std::string & inputFile );
};

#endif
