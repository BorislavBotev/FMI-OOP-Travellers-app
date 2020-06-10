#include "Destination.hpp"
Destination::Destination()
{
    name=NULL;
    period=NULL;
    grade=0;
    comment=NULL;
    photos=NULL;
    photosSize=0;

}
Destination::~Destination()
{
    delete[]name;
    delete period;
    delete[]comment;
    deleteArray(photos,photosSize);
}
void Destination::setName(char*name)
{
    if(!name)
    {
        throw MyException("NULL pointer");
    }
    int len=strlen(name);
    if(len==0)
    {
        throw MyException("Empty name given!");
    }
    int index=0;
    char*town=NULL;
    extractNameFromInput(town,name,index);
    if(!town)
    {
        throw MyException("Invalid town");
    }
    if(name[index]!=',' || name[++index]!=' ')
    {
        delete[]town;
        throw MyException("Invalid syntax- Town, Country");
    }
    index++;
    char*country=NULL;
    extractWordFromInput(country,name,index);
    if(!country || name[index]!='\0')
    {
        delete[]town;
        delete[]country;
        throw MyException("Invalid country");
    }
    this->name=new char[len+1];
    strcpy(this->name,name);
    delete[]town;
    delete[]country;
}
void Destination::setPeriod(char* date1,char*date2)
{
    delete period;
    period=new TimePeriod();
    try
    {
        period->setFrom(date1);
        period->setTill(date2);
    }
    catch(MyException e)
    {
        delete period;
        throw MyException(e.what());
    }
}
void Destination::setGrade(int grade)
{
    if(grade<1 || grade>5)
    {
        throw MyException("Invalid grade-it should be between 1 and 5");
    }
    this->grade=grade;
}
void Destination::setComment(char*comment)
{
    if(!comment)
    {
        throw MyException("NULL pointer");
    }
    this->comment=new char[strlen(comment)+1];
    strcpy(this->comment,comment);
}
void Destination::addPhoto(char*file)
{
    if(photosSize==MAX_PHOTOS_PER_USER)
    {
        throw MyException("You already uploaded enough pictures I am sorry");
    }
    try
    {
        photos[photosSize]=new Photo(file);
        photosSize++;
    }
    catch(MyException e)
    {
        delete photos[photosSize];
        throw MyException(e.what());
    }
}
int Destination::getPhotosSize()const
{
    return photosSize;
}





