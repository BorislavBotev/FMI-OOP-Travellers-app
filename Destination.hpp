#ifndef DESTINATION_HPP_INCLUDED
#define DESTINATION_HPP_INCLUDED
#include "TimePeriod.hpp"
#include "Photo.hpp"
const int MAX_DESTINATIOON_NAME_LENGTH=30;
class Destination
{
    char*name;
    TimePeriod*period;
    int grade;
    char*comment;
    Photo**photos;
};

#endif
