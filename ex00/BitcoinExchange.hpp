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

struct btcdate {
    int year;
    int month;
    int day;
};

class BitcoinExchange
{
private:

    static const std::string        DATA_FILE_NAME;
    static const std::string        DATA_FILE_DELEMITER;
    static const std::string        INPUT_FILE_DELEMITER;
    static const double             INPUT_MAX_VALUE;
    static const double             INPUT_MIN_VALUE;

    std::map<btcdate, double>   _data;

    void    loadData( void );

public:

    BitcoinExchange( void );
    BitcoinExchange( const BitcoinExchange & ref );
    ~BitcoinExchange();

    BitcoinExchange & operator=( const BitcoinExchange & ref );

    void run( const std::string & inputFile );
};

#endif
