#ifndef DESTINATIONSARCHIVE_HPP_INCLUDED
#define DESTINATIONSARCHIVE_HPP_INCLUDED
#include <fstream>
#include <iostream>
#include <cstring>
#include "Structs.hpp"
#include "UsersArchive.hpp"
class DestinationsArchive
{
    //Destination** destinations;
    int destinationsSize;
    int destinationsCapacity;
    FileDestination*fDestinations;

public:
    void registerUser(FileUser*users);
    void viewDestinationsRatings(FileDestination& destination);
    void printDestinations(FileDestination* destinations);
    void viewDestinations(int& command);

};

#endif // DESTINATIONSARCHIVE_HPP_INCLUDED
