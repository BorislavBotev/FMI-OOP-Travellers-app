#ifndef USER_HPP_INCLUDED
#define USER_HPP_INCLUDED
#include "Destination.hpp"
#include <cstring>
const int MAX_NAME_LENGTH=30;
const int MAX_PASSWORD_LENGTH=10;
const int MAX_MAIL_LENGTH=20;
class User
{
private:
    char*name;
    char** friends;
    int friendsSize;
    int friendsCapacity;
    bool isUpToDate;
    Destination**destinations;
    int destinationsSize;
    int destinationsCapacity;
    bool isFileUpdated;

    bool alreadyInYourList(const char*name);
public:
    User(char*name);
    ~User();
    const char* getName()const;
    char* addDestination();
    void addFriend(const char*name);
    void viewFriends();
    void addFriendWtihValidation(const char*username);
    bool upToDate()
    {
        return isUpToDate;
    };
    int getFriendsSize() const
    {
        return friendsSize;
    }
    int getDestinationsSize() const
    {
        return destinationsSize;
    }
    char** getFriends() const
    {
        return friends;
    }

};


#endif
