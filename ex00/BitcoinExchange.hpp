/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasouza <gasouza@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:21:39 by gasouza           #+#    #+#             */
/*   Updated: 2024/04/07 20:03:11 by gasouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_H
# define BITCOIN_EXCHANGE_H

# include <string>
# include <map>

struct BtcDate
{
    int year;
    int month;
    int day;

    bool operator<( const BtcDate &ref ) const;
    bool operator>( const BtcDate &ref ) const;
    bool operator==( const BtcDate &ref ) const;
    bool operator!=( const BtcDate &ref ) const;
};

class BitcoinExchange
{
private:

    static const std::string    DATA_FILE_NAME;
    static const std::string    DATA_FILE_DELEMITER;
    static const std::string    INPUT_FILE_DELEMITER;
    static const double         INPUT_MAX_VALUE;
    static const double         INPUT_MIN_VALUE;

    std::map<BtcDate, double>   _data;

    void    loadData( void );

public:

    BitcoinExchange( void );
    BitcoinExchange( const BitcoinExchange & ref );
    ~BitcoinExchange( void );

    BitcoinExchange & operator=( const BitcoinExchange & ref );

    void run( const std::string & inputFile );
};

#endif
