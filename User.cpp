#include "User.hpp"
User::User(char*name)
{
    if(name)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
    }
    friendsSize=0;
    friendsCapacity=5;
    isUpToDate=true;
    friends=new char*[friendsCapacity];
}

User::~User()
{
    delete[]name;
    deleteArray(friends,friendsSize);
}
const char*User:: getName()const
{
    return name;
}

void User::addFriend(const char*name)
{
    if(!name)
    {
        return;
    }
    if(friendsSize==friendsCapacity)
    {
        resizeArray(friends,friendsSize,friendsCapacity);
    }
    friends[friendsSize]=new char[strlen(name)+1];
    strcpy(friends[friendsSize],name);
    std::cout<<"Successfully added : "<<name<<std::endl;
    friendsSize++;
    std::cout<<friendsSize<<std::endl;
    isUpToDate=false;
}
void User::viewFriends()
{
    if(friendsSize==0)
    {
        std::cout<<"You have no friends :("<<std::endl;
        return;
    }
    std::cout<<"View friends "<<friendsSize<<std::endl;
    for(int i=0; i<friendsSize; i++)
    {
        std::cout<<i+1<<"- "<<friends[i]<<std::endl;
    }
}
void User::addFriendWtihValidation(const char*username)
{
    if(strcmp(name,username)==0)
    {
        std::cout<<"You can't add yourself as a friend i am sorry"<<std::endl;
        return;
    }
    for(int i=0; i<friendsSize; i++)
    {
        if(strcmp(username,friends[i])==0)
        {
            std::cout<<"You are already friend with "<<username<<std::endl;
            return;
        }
    }
    addFriend(username);

}


void User::addDestination(Destination&des)
{

}
