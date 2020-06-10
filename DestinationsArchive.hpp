#ifndef DESTINATIONSARCHIVE_HPP_INCLUDED
#define DESTINATIONSARCHIVE_HPP_INCLUDED
#include <fstream>
#include <iostream>
#include <cstring>
#include "Structs.hpp"
#include "UsersArchive.hpp"
const char DES_ARCHIVE_NAME[][16]= {"destinations.db"};
class DestinationsArchive
{
    int destinationsSize;
    int destinationsCapacity;
    FileDestination*fDestinations;

public:
    //  void registerUser(FileUser*users);
    // void viewDestinationsRatings(FileDestination& destination);
    DestinationsArchive();
    ~DestinationsArchive();
    void collectAllData();
    void printDestinations();
                        void addDestination(char*des);

    // void viewDestinations(int& command);

};

#endif // DESTINATIONSARCHIVE_HPP_INCLUDED
