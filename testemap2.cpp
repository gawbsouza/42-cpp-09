#include <iostream>
#include <map>

// Definição da estrutura btcdate
struct BtcDate {
    int year;
    int month;
    int day;

    // Operador de comparação para a estrutura btcdate
    bool operator<(const BtcDate& other) const {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        return day < other.day;
    }
};

int main() {
    // Criando um mapa onde a chave é btcdate e o valor é um double (pode ser substituído pelo tipo que desejar)
    std::map<BtcDate, double> btc_prices;

    // Inserindo alguns valores no mapa
    btc_prices[{2024, 4, 7}] = 50000.0;
    btc_prices[{2024, 4, 6}] = 48000.0;
    btc_prices[{2024, 4, 5}] = 49000.0;

    // Iterando sobre o mapa e imprimindo os valores
    for (const auto& pair : btc_prices) {
        std::cout << "Data: " << pair.first.year << "-" << pair.first.month << "-" << pair.first.day
                  << ", Preço: " << pair.second << std::endl;
    }

    return 0;
}