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
    char input2[MAX_DATE_LENGTH];
    while(true)
    {
        std::cout<<"Write destinations period\nFrom:"<<std::endl;
        std::cin.getline(input,MAX_DESTINATIOON_NAME_LENGTH);
        std::cout<<"Till:"<<std::endl;
        std::cin.getline(input2,MAX_DATE_LENGTH);
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
    std::cin.getline(input,MAX_COMMENT_LENGTH);
    while(strcmp(input,"exit")!=0 || des->getPhotosSize()<=MAX_PHOTOS_PER_USER)
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
        std::cin.getline(input,MAX_COMMENT_LENGTH);
    }
    if(destinationsSize==destinationsCapacity)
    {
        resizeArray(destinations,destinationsSize,destinationsCapacity);
    }
    destinations[destinationsSize++]=des;
    isUpToDate=false;
    return des->getName();
}
bool User::alreadyInYourList(const char*name)
{
    for(int i=0;i<destinationsSize;i++)
    {
        if(strcmp(destinations[i]->getName(),name)==0)
        {
            return true;
        }
    }
    return false;
}
