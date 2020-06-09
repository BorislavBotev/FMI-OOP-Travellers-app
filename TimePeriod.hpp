#ifndef TIMEPERIOD_HPP_INCLUDED
#define TIMEPERIOD_HPP_INCLUDED
#include <iostream>
#include <ctime>
#include "GlobalFunctions.hpp"
#include "MyException.hpp"
const int MINIMUM_YEAR=1950;
class TimePeriod
{
    char*from;
    char*till;
    bool isValidDateFormat(const char*date);
    bool isValidFrom(const char*date);
    bool isValidTill(const char*date);
    bool isPreviousDate(const char*first,const char*second);
    bool isAfterCurrentDate(const char*date);
public:
    TimePeriod();
    ~TimePeriod();
    void setFrom(char*date);
    void setTill(char*date);
    const char* getFrom() const;
    const char* getTill() const;
};
std::ostream& operator<<(std::ostream& os, TimePeriod const& t);


#endif
