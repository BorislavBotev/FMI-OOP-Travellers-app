#include "UsersArchive.hpp"
UsersArchive::UsersArchive()
{
    users=NULL;
    fUsers=NULL;
    usersCapacity=5;
    usersSize=0;
}

FileUser* UsersArchive:: downloadUsers()
{
    std::ifstream iFile("users.db",std::ios::binary);
    if(iFile.bad())
    {
        iFile.close();
        throw MyException("Can not open file");
    }
    iFile.read((char*)&usersSize,sizeof(int));

    if(usersSize==0)
    {
        return NULL;
    }
    usersCapacity=usersSize+5;
    FileUser*users=new FileUser[usersSize];
    iFile.read((char*)users,(sizeof(FileUser)*usersSize));
    if(users==NULL)
    {
        iFile.close();
        throw MyException("Can not read database");
    }
    iFile.close();
    return users;
}

User* UsersArchive::signIn()
{

    if(fUsers==NULL)
    {
        fUsers=downloadUsers();
    }
    if(usersSize==0)
    {
        std::cout<<"No registered users"<<std::endl;
        return registerUser();
    }
    while(true)
    {
        int i=0;
        std::cout<<"Username:"<<std::endl;
        char name[30];
        std::cin.getline(name,30);
        std::cout<<"Password:"<<std::endl;
        char password[10];
        std::cin.getline(password,10);
        for(; i<usersSize; i++)
        {
            if(strcmp(name,fUsers[i].name)==0 && strcmp(password,fUsers[i].password)==0)
            {
                break;
            }
        }
        if(i!=usersSize)
        {
            std::cout<<"Successfully signed in!"<<std::endl;
            fileUsersToArrUsers();
            if(users==NULL)
            {
                throw MyException("Can not copy users from database");
            }
            delete[] fUsers;
            fUsers=NULL;
            return users[i];
        }
        std::cout<<"Invalid username or password"<<std::endl;
    }
}

User* UsersArchive::registerUser()
{
    if(fUsers==NULL)
    {
        fUsers=downloadUsers();
    }
    while(true)
    {
        int i=0;
        std::cout<<"Username:"<<std::endl;
        char name[30];
        std::cin.getline(name,30);
        std::cout<<"Password:"<<std::endl;
        char password[30];
        std::cin.getline(password,10);
        std::cout<<"Mail:"<<std::endl;
        char mail[30];
        std::cin.getline(mail,20);
        for(; i<usersSize; i++)
        {
            if(strcmp(name,fUsers[i].name)==0 && strcmp(mail,fUsers[i].mail)==0)
            {
                break;
            }
        }
        if(i==usersSize)
        {
            addNewUserToFile(FileUser(name,password,mail));
            User* user=new User(name);
            usersSize++;
            char*n=createFileNameFromUsername(name);
            delete[]n;
            return user;
        }
        std::cout<<"Username or mail already used"<<std::endl;
    }
}

void UsersArchive::addNewUserToFile(FileUser fileUser)
{
    int count=usersSize+1;
    std::ofstream oFile("users.db",std::ios::binary);
    if(!oFile.is_open())
    {
        throw MyException("Can not open file");
    }
    oFile.seekp(0);
    oFile.write((char const*)&count,sizeof(int));
    for(int i=0; i<usersSize; i++)
    {
        oFile.write((char const*)&fUsers[i],sizeof(FileUser));
    }
    oFile.write((char const*)&fileUser,sizeof(FileUser));
    oFile.close();
}

void UsersArchive::printUsers()
{
    try
    {
        fUsers=downloadUsers();
    }
    catch(MyException e)
    {
        std::cout<<e.what()<<std::endl;
        return;
    }
    for(int i=0; i<usersSize; i++)
    {
        std::cout<<i+1<<"- "<<fUsers[i].name<<std::endl;
    }
}

void UsersArchive::fileUsersToArrUsers()
{
    if(fUsers==NULL)
    {
        return;
    }
    users=new User*[usersCapacity];
    for(int i=0; i<usersSize; i++)
    {
        users[i]=new User(fUsers[i].name);
    }
    for(int i=0; i<usersSize; i++)
    {
        std::cout<<users[i]->getName()<<std::endl;
    }
}
void UsersArchive::collectAllData()
{
    for(int i=0; i<usersSize; i++)
    {
        char*fName=createFileNameFromUsername(users[i]->getName());
        if(!fName)
        {
            throw MyException("User DB corrupted");
        }

        std::ifstream iFile(fName,std::ios::binary);
        if(iFile.bad())
        {
            iFile.close();
            throw MyException("Can not open file");
        }
        int friends=0,dest=0;
        iFile.read((char*)&friends,sizeof(int));
        iFile.read((char*)&dest,sizeof(int));
        FileFriends*fFriends=new FileFriends[friends];
        FileUsersDestination*userDes=new FileUsersDestination[dest];
        iFile.read((char*)fFriends,(sizeof(FileFriends)*friends));
        iFile.read((char*)userDes,(sizeof(FileUsersDestination)*dest));
        if(fFriends==NULL || userDes==NULL)
        {
            delete[]fFriends;
            delete[] userDes;
            iFile.close();
            throw MyException("Can not read file");
        }
        for(int j=0; j<friends; j++)
        {
            users[i]->addFriend(fFriends[j].name);
        }
        for(int j=0; j<dest; j++)
        {
            Destination*d=&usersDestinationsToDestination(userDes[j]);
            try
            {
                users[i]->addDestinationFromFile(*d);
            }
            catch(MyException e)
            {
                std::cout<<e.what()<<std::endl;
            }
        }
        delete[]fFriends;
        delete[] userDes;
        iFile.close();
    }

}


void UsersArchive::updateUserInDB(User& user)
{
    if(user.upToDate())
    {
        return;
    }
    char*name=createFileNameFromUsername(user.getName());
    std::ofstream oFile(name,std::ios::binary);
    if(oFile.bad())
    {
        oFile.close();
        throw MyException("File is corrupted-can not save");
    }
    int countFriends=user.getFriendsSize();
    int countDestinations=user.getDestinationsSize();
    oFile.seekp(0);
    oFile.write((char const*)&countFriends,sizeof(int));
    oFile.write((char const*)&countDestinations,sizeof(int));
    FileFriends* f=new FileFriends[countFriends];
    char**friends=user.getFriends();

    for(int i=0; i<countFriends; i++)
    {
        f[i]=FileFriends(friends[i]);
        oFile.write((char const*)&f[i],sizeof(FileFriends));
    }
    for(int i=0; i<countDestinations; i++)
    {
        try
        {
            createFileUsersDestinationFromDestinationAndWriteIT(user.getMyDestinationByIndex(i),oFile);
        }
        catch(MyException e)
        {
            std::cout<<"Can not write destination with index "<<i<<std::endl;
        }
    }
    delete[] f;
    oFile.close();
}

bool UsersArchive::isNameValidUser(const char*username)
{
    if(usersSize==0)
    {
        return false;
    }
    for(int i=0; i<usersSize; i++)
    {
        if(strcmp(users[i]->getName(),username)==0)
        {
            return true;
        }
    }
    return false;
}
void UsersArchive::createFileUsersDestinationFromDestinationAndWriteIT(Destination&des,std::ofstream&os)
{
    char ph[5][10];
    if(des.getPhotosSize()==0)
    {
        strcpy(ph[0],"");
    }
    for(int i=0; i<des.getPhotosSize(); i++)
    {
        strcpy(ph[i],des.getPhotos()[i]->getName());
    }
    FileUsersDestination f(des.getName(),des.getPeriod()->getFrom(),des.getPeriod()->getTill(),des.getGrade(),des.getComment(),ph);
    os.write((char const*)&f,sizeof(FileUsersDestination));
}

Destination& UsersArchive::usersDestinationsToDestination(FileUsersDestination& userDes)
{
    Destination*d=new Destination();
    d->setName(userDes.name);
    d->setGrade(userDes.rating);
    d->setPeriod(userDes.from,userDes.till);
    d->setComment(userDes.comment);
    for(int i=0; i<MAX_PHOTOS_PER_USER; i++)
    {
        try
        {
            d->addPhoto(userDes.photos[i]);
        }
        catch(MyException e)
        {
            break;
        }
    }
    return *d;
}


