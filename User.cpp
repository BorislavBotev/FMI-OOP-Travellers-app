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
    destinationsSize=0;
    destinationsCapacity=5;
    isUpToDate=true;
    friends=new char*[friendsCapacity];
    destinations=new Destination*[destinationsCapacity];
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
void User::addDestinationFromFile(Destination&des)
{
    if(destinationsSize==destinationsCapacity)
    {
        resizeArray(destinations,destinationsSize,destinationsCapacity);
    }
    destinations[destinationsSize++]=&des;
}

char* User::addDestination()
{
    Destination*des=new Destination();
    char input[100];
    while(true)
    {
        std::cout<<"Write destinations name"<<std::endl;
        std::cin.getline(input,MAX_DESTINATIOON_NAME_LENGTH);
        try
        {
            des->setName(input);
            break;
        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
        }
    }
    if(alreadyInYourList(input))
    {
        std::cout<<"Already in your list"<<std::endl;
        delete des;
        return NULL;
    }
    int n=0;
    while(true)
    {
        std::cout<<"Write destinations grade"<<std::endl;
        std::cin>>n;
        std::cin.ignore();
        try
        {
            des->setGrade(n);
            break;
        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
        }
    }
    char input2[50];
    while(true)
    {
        std::cout<<"Write destinations period\nFrom:"<<std::endl;
        std::cin.getline(input,MAX_DATE_LENGTH+1);
        std::cout<<"Till:"<<std::endl;
        std::cin.getline(input2,MAX_DATE_LENGTH+1);
        try
        {
            des->setPeriod(input,input2);
            break;
        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
        }
    }
    while(true)
    {
        std::cout<<"Write destinations comment"<<std::endl;
        std::cin.getline(input,MAX_COMMENT_LENGTH);
        try
        {
            des->setComment(input);
            break;
        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
        }
    }

    std::cout<<"Add photos if you want- exit if you wanna leave"<<std::endl;
    std::cin.getline(input,FILE_EXTENSIONS_MAX_LEN+1);
    while(strcmp(input,"exit")!=0 && des->getPhotosSize()<=MAX_PHOTOS_PER_USER)
    {
        try
        {
            des->addPhoto(input);
        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
        }
        std::cout<<"Add photos if you want-exit for leave"<<std::endl;
        std::cin.getline(input,FILE_EXTENSIONS_MAX_LEN+1);
    }
    if(destinationsSize==destinationsCapacity)
    {
        resizeArray(destinations,destinationsSize,destinationsCapacity);
    }
    destinations[destinationsSize++]=des;
    isUpToDate=false;
    std::cout<<"HELLOOOOOOOO"<<std::endl;
    return des->getName();
}
            void User::viewMyDestinations()
            {
                if(destinationsSize==0)
                {
                    std::cout<<"You haven't visited any destinations"<<std::endl;
                    return;
                }
                for(int i=0;i<destinationsSize;i++)
                {
                    std::cout<<*destinations[i]<<std::endl;
                }
            }


Destination& User::getMyDestinationByIndex(int number)
{
    if(number<0 && number>=destinationsSize)
    {
        throw MyException("Invalid index");
    }
    return *destinations[number];
}


bool User::alreadyInYourList(const char*name)
{
    for(int i=0; i<destinationsSize; i++)
    {
        if(strcmp(destinations[i]->getName(),name)==0)
        {
            return true;
        }
    }
    return false;
}


