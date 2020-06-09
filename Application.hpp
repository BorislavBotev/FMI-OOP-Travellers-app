#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED
#include "User.hpp"
#include <fstream>
#include <iostream>
#include "UsersArchive.hpp"
#include "DestinationsArchive.hpp"
#include <cstring>

class Application
{
    private:
    User* user;
    int command;
   // bool exit;
  //  int countUsers;
  //  int countDestinations;
    UsersArchive* usArchive;
    DestinationsArchive* desArchive;

    public:

    Application();
    ~Application();
  //  FileUser* downloadUsers();
   // void signIn(FileUser*);
   // void registerUser(FileUser*);
   // void addNewUserToFile(FileUser&);
  //  void printUsers(FileUser*);
   // void viewDestinations();
  //  void printDestinations(FileDestination*destinations);
  //  void viewDestinationsRatings(FileDestination& destination);
  //  void addFriend();

    void app();
    void logIn();
    void homepage();



        //
};


#endif
