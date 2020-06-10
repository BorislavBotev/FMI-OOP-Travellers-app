#ifndef PHOTO_HPP_INCLUDED
#define PHOTO_HPP_INCLUDED
#include <iostream>
#include "MyException.hpp"
#include "GlobalFunctions.hpp"
const int FILE_EXTENSIONS_COUNT=2;
const int FILE_EXTENSIONS_MAX_LEN=10;
const char FILE_EXTENSIONS[FILE_EXTENSIONS_COUNT][FILE_EXTENSIONS_MAX_LEN]={"png","jpeg"};
class Photo
{
    char*name;
    bool isValidFileName(const char*name);
    bool isPhotoFileLetter(char l);

public:
    Photo(const char*n);
    ~Photo();
    const char* getName() const;

};
std::ostream& operator<<(std::ostream& os, Photo const& t);



#endif // PHOTO_HPP_INCLUDED
