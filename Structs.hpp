#ifndef STRUCTS_HPP_INCLUDED
#define STRUCTS_HPP_INCLUDED
#include "User.hpp"
#include "Photo.hpp"
struct FileUsersDestination
{
    char name[MAX_DESTINATIOON_NAME_LENGTH];
    char from[MAX_DATE_LENGTH];
    char till[MAX_DATE_LENGTH];
    int rating;
    char comment[MAX_COMMENT_LENGTH];
    char photos[MAX_PHOTOS_PER_USER][FILE_EXTENSIONS_MAX_LEN];
    FileUsersDestination(char*name,char*from,char*till,int rating,char*comment,char photos[MAX_PHOTOS_PER_USER][FILE_EXTENSIONS_MAX_LEN])
    {
        strcpy(this->name,name);
        strcpy(this->from,from);
        strcpy(this->till,till);
        this->rating=rating;
       for(int i=0;i<MAX_PHOTOS_PER_USER;i++)
       {
           strcpy(this->photos[i],photos[i]);
       }

    }
    FileUsersDestination()
    {

    }
};
struct FileFriends
{
    char name[MAX_NAME_LENGTH];
    FileFriends(char*name)
    {
        strcpy(this->name,name);
    }
    FileFriends(){}

};
struct FileUser
{
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char mail[MAX_MAIL_LENGTH];
    FileUser(char*name,char*password,char*mail)
    {
        strcpy(this->name,name);
        strcpy(this->password,password);
        strcpy(this->mail,mail);
    }
    FileUser()
    {

    }
};
struct FileDestination
{
    char name[MAX_DESTINATIOON_NAME_LENGTH];
        FileDestination(char*name)
    {
        strcpy(this->name,name);
    }
      FileDestination()
    {

    }

};


#endif
