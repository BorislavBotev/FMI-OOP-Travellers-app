#ifndef DESTINATION_HPP_INCLUDED
#define DESTINATION_HPP_INCLUDED
#include "TimePeriod.hpp"
#include "Photo.hpp"
const int MAX_DESTINATIOON_NAME_LENGTH=30;
const int MAX_PHOTOS_PER_USER=5;
const int MAX_COMMENT_LENGTH=100;
class Destination
{
    char*name;
    TimePeriod*period;
    int grade;
    char*comment;
    Photo**photos;
    int photosSize;
public:
    Destination();
    ~Destination();
    void setName(char*name);
    void setPeriod(char* date1,char*date2);
    void setGrade(int grade);
    void setComment(char*comment);
    void addPhoto(char*file);
    int getPhotosSize()const;
    char* getName()const;
    int getGrade()const;
    TimePeriod* getPeriod()const;
    char* getComment()const;
    Photo** getPhotos()const;
};
std::ostream& operator<<(std::ostream& os, Destination const& d);


#endif
