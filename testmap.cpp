
#include <map>
#include <iostream>

using namespace std;

struct BtcDate {

    int year;
    int month;
    int day;

    bool operator<(const BtcDate &ref) const {
        if (year != ref.year) return year < ref.year;
        if (month != ref.month) return month < ref.month;
        return day < ref.day;
    }

    bool operator>(const BtcDate &ref) const {
        if (year != ref.year) return year > ref.year;
        if (month != ref.month) return month > ref.month;
        return day > ref.day;
    }

    bool operator==(const BtcDate &ref) const {
        return year == ref.year && month == ref.month && day == ref.day;
    }

    bool operator!=(const BtcDate &ref) const {
        return year != ref.year || month != ref.month || day != ref.day;
    }

};


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


int main()
{
    std::map<BtcDate, double> mymap;

    mymap[{2024, 2, 5}] = 1;
    mymap[{2024, 1, 31}] = 2;
    mymap[{2024, 1, 5}] = 3;
    mymap[{2024, 5, 28}] = 4;
    mymap[{2024, 4, 1}] = 5;

    std::map<BtcDate, double>::iterator it = mymap.begin();

    for (; it != mymap.end(); it++) {

        BtcDate key = it->first;
        int value = it->second;

        cout << "[" << key.year << "-" << key.month << "-" << key.day << "] = " << value << endl;
    }

    BtcDate toFind = {2024, 1, 4};

    double value = findOnMap(toFind, mymap);

    cout << "value found: " << value << endl;

    return 0;

}