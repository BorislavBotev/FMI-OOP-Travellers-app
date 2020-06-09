#ifndef USERSARCHIVE_HPP_INCLUDED
#define USERSARCHIVE_HPP_INCLUDED
#include <fstream>
#include <iostream>
#include <cstring>
#include "Structs.hpp"
class UsersArchive
{
    User** users;
    int usersSize;
    int usersCapacity;
    FileUser*fUsers;
    void addNewUserToFile(FileUser fileUser);
    void fileUsersToArrUsers();
    FileUser* downloadUsers();
    Destination& usersDestinationsToDestination(UsersDestination& userDes);


public:
    bool isNameValidUser(const char*username);

    void collectAllData();
    UsersArchive();
    User* signIn();
    User* registerUser();
    void printUsers();
    void userInfoForDestination(char*name);
    void updateUserInDB(User& user);


};


#endif
