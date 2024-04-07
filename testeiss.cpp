#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <exception>

using namespace std;

struct btcdate {
    int year;
    int month;
    int day;
};


std::string removeSpaces(std::string str) 
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    return str;
}

btcdate parseString(std::string & str, char delemiter)
{
    btcdate d;
    char del[2];
    std::istringstream stream(str);

    stream >> d.year >> del[0] >> d.month >> del[1] >> d.day;

    if (del[0] != delemiter || del[1] != delemiter || !stream.eof()) {
        throw std::invalid_argument("invalid format");
    }

    return d;
}

double parseNumber(std::string & str)
{
    std::istringstream stream(str);
    double number;

    stream >> number;
    if (!stream.eof()) {
        throw std::invalid_argument("invalid format");
    }

    return number;
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

int main()
{
    string input;

    cin >> input;
    double num = parseNumber(input);
    cout << num << endl;

//     btcdate date;

//     cin >> input;
//     cout << "entrada: " << removeSpaces(input) << endl;

//     try {
//         date = parseString(input, '-');
//     } catch (exception & e) {
//         cout << e.what() << endl;
//         return 1;
//     }

//     if (!isValidDate(date)) {
//         cout << "invalid date!" << endl;
//         return 1;
//     }

//    cout << "date: " << date.year << " " << date.month << " " << date.day << endl;

}