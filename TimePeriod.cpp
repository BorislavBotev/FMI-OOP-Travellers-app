#include "TimePeriod.hpp"
TimePeriod::TimePeriod():from(NULL),till(NULL) {}
TimePeriod::~TimePeriod()
{
    delete[] from;
    delete[] till;
}

void TimePeriod::setFrom(char*date)
{
    if(!date)
    {
        throw MyException("NULL pointer given!");
    }
    if(!isValidFrom(date))
    {
        throw MyException("Invalid date given-make sure it is in YYYY-MM-DD format and it is a real date(after 1950)");
    }
    delete[] from;
    createString(from,date);
}

void TimePeriod::setTill(char*date)
{
    if(!date)
    {
        throw MyException("NULL pointer given!");
    }
    if(!isValidTill(date))
    {
        throw MyException("Invalid date given-make sure it is in YYYY-MM-DD format and it is a real date(after 1950 and the starting date)");
    }
    delete[] till;
    createString(till,date);
}

bool TimePeriod::isValidFrom(const char*date)
{
    int i=0;
    int year=extractNumberFromString(date,i);
    if(year<MINIMUM_YEAR)
    {
        return false;
    }
    if(!isValidDateFormat(date))
    {
        return false;
    }
    if(isAfterCurrentDate(date))
    {
        return false;
    }
    return true;
}

bool TimePeriod::isValidTill(const char*date)
{
    if(!from)
    {
        return false;
    }
    if(!isValidDateFormat(date))
    {
        return false;
    }
    if(!isPreviousDate(from,date))
    {
        return false;
    }
    if(isAfterCurrentDate(date))
    {
        return false;
    }
    return true;
}
bool TimePeriod::isPreviousDate(const char*first,const char*second)
{
    int i1=0,i2=0;
    int numberFirst=extractNumberFromString(first,i1);
    int numberSecond=extractNumberFromString(second,i2);
    if(numberSecond<numberFirst)
    {
        return false;
    }
    else if(numberSecond>numberFirst)
    {
        return true;
    }
    numberFirst=extractNumberFromString(first,++i1);
    numberSecond=extractNumberFromString(second,++i2);
    if(numberSecond<numberFirst)
    {
        return false;
    }
    else if(numberSecond>numberFirst)
    {
        return true;
    }
    numberFirst=extractNumberFromString(first,++i1);
    numberSecond=extractNumberFromString(second,++i2);
    if(numberSecond<numberFirst)
    {
        return false;
    }
    return true;
}
//using ctime to get the current time
bool TimePeriod::isAfterCurrentDate(const char*date)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int i=0;
    int number=extractNumberFromString(date,i);
    if(number>(1900+ltm->tm_year))
    {
            std::cout<<ltm->tm_year;

        return true;
    }
    else if(number<(1900+ltm->tm_year))
    {
        return false;
    }
    number=extractNumberFromString(date,++i);
    if(number>(1+ltm->tm_mon))
    {
        return true;
    }
    else if(number>(1+ltm->tm_mon))
    {
        return false;
    }
    number=extractNumberFromString(date,++i);
    return number>ltm->tm_mday?true:false;
}

bool TimePeriod::isValidDateFormat(const char*date)
{
    if(!date)
    {
        return false;
    }
    int year=0,month=0,day=0,index=0;
    if(date[index]==0)
    {
        return false;
    }
    year=extractNumberFromString(date,index);
    if(year==0 || date[index++]!='-')
    {
        return false;
    }
    month=extractNumberFromString(date,index);
    if(month==0 || month>12 || (month<10 && date[index-2]!='0' && date[index-3]!='-') || (month>=10 && date[index-3]!='-') || date[index++]!='-')
    {
        return false;
    }
    day=extractNumberFromString(date,index);
    if(date[index]!='\0' || day==0 || day>31 || (day<10 && date[index-2]!='0' && date[index-3]!='-') || (day>=10 && date[index-3]!='-'))
    {
        return false;
    }
    if((month==4 || month==6 || month==9 || month==11) && day==31)
    {
        return false;
    }
    if(month==2 && (day>=28 || (day==27 && year%4==0)))
    {
        return false;
    }
    return true;
}
const char* TimePeriod:: getFrom() const
{
    return from;
}
const char* TimePeriod::getTill() const
{
    return till;
}



std::ostream& operator<<(std::ostream& os, TimePeriod const& t)
{
    return os<<t.getFrom()<<"\n"<<t.getTill()<<std::endl;
}
