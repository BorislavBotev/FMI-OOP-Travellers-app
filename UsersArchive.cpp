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
    std::cout<<"users after file"<<usersSize<<std::endl;

    if(usersSize==0)
    {
        return NULL;
    }
    usersCapacity=usersSize+5;
    //std::cout<<usersSize<<std::endl;
    FileUser*users=new FileUser[usersSize];
    // iFile.seekg(sizeof(int),std::ios::beg);
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
        //for(int i=0;i<usersSize;i++)
        // {
        //     std::cout<<fUsers->name<<fUsers->password<<fUsers->mail<<std::endl;
        //  }
    }
    if(usersSize==0)
    {
        std::cout<<"No registered users"<<std::endl;
        return NULL;
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
            std::cout<<fUsers[i].name<<fUsers[i].password<<std::endl;

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
            std::cout<<users[i]->getName()<<std::endl;

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
            std:: cout<<"hi"<<std::endl;
            if(strcmp(name,fUsers[i].name)==0 && strcmp(mail,fUsers[i].mail)==0)
            {
                break;
            }
        }
        if(i==usersSize)
        {
            addNewUserToFile(FileUser(name,password,mail));
            User* user=new User(name);
            // std:: cout<<"hi"<<std::endl;

            //addNewUserToFile(user);
            //this->user=new User(name);
            std::cout<<"Successfully registered!"<<std::endl;
            //  std::cout<<usersSize<<std::endl;
            //             std::cout<<users<<std::endl;
            usersSize++;
            char*n=createFileNameFromUsername(name);
            std::cout<<n<<std::endl;
            std::ofstream i;
            i.open(n);
            i.close();
            delete[]n;
            return user;
        }
        std::cout<<"Username or mail already used"<<std::endl;
    }
}

void UsersArchive::addNewUserToFile(FileUser fileUser)
{
    int count=usersSize+1;
    // std::cout<<fileUser.name<<" "<<fileUser.password<<" "<<fileUser.mail<<std::endl;
    std::ofstream oFile("users.db",std::ios::binary);
    if(!oFile.is_open())
    {
        throw MyException("Can not open file");
    }
    oFile.seekp(0);
    oFile.write((char const*)&count,sizeof(int));
    // std::cout<<count<<std::endl;
    //oFile.seekp(0);
    for(int i=0; i<usersSize; i++)
    {
        oFile.write((char const*)&fUsers[i],sizeof(FileUser));
    }
    std::cout<<fileUser.name<<fileUser.password<<std::endl;

    oFile.write((char const*)&fileUser,sizeof(FileUser));
    oFile.close();
    //std:: cout<<"hi"<<std::endl;
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
        std::cout<<"HIIIIIIIIIII"<<std::endl;

        std::ifstream iFile(fName,std::ios::binary);
        if(iFile.bad())
        {
            iFile.close();
            throw MyException("Can not open file");
        }
        int friends=0,dest=0;
        iFile.read((char*)&friends,sizeof(int));
        //std::cout<<"users after file"<<usersSize<<std::endl;
        iFile.read((char*)&dest,sizeof(int));

        std::cout<<"friends::"<<friends<<std::endl;
        std::cout<<"dest:"<<dest<<std::endl;

        FileFriends*fFriends=new FileFriends[friends];
        UsersDestination*userDes=new UsersDestination[dest];
        iFile.read((char*)fFriends,(sizeof(FileFriends)*friends));
        iFile.read((char*)userDes,(sizeof(UsersDestination)*dest));
        if(fFriends==NULL || userDes==NULL)
        {
            delete[]fFriends;
            delete[] userDes;
            iFile.close();
            throw MyException("Can not read file");
        }
        for(int j=0; j<friends; j++)
        {
            std::cout<<fFriends[j].name<<std::endl;
            users[i]->addFriend(fFriends[j].name);
        }
        /*for(int j=0; j<dest; j++)
        {
            Destination*d=&usersDestinationsToDestination(userDes[j]);
            try
            {
                users[i]->addDestination(*d);
            }
            catch(MyException e)
            {
                std::cout<<e.what()<<std::endl;
            }
        }*/
        delete[]fFriends;
        delete[] userDes;
        iFile.close();
    }

}
Destination& UsersArchive::usersDestinationsToDestination(UsersDestination& userDes)
{

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
        throw MyException("File is corrupted");
    }
    int countFriends=user.getFriendsSize();
    oFile.seekp(0);
    oFile.write((char const*)&countFriends,sizeof(int));
    //shte bude za destinaciite
    oFile.write((char const*)&countFriends,sizeof(int));
    FileFriends* f=new FileFriends[countFriends];
   char**friends=user.getFriends();

    for(int i=0;i<countFriends;i++)
    {
        f[i]=FileFriends(friends[i]);
               std::cout<<f[i].name<<std::endl;

        oFile.write((char const*)&f[i],sizeof(FileFriends));
    }
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






/*void UsersArchive::userInfoForDestination(char*name)
{
    for(int i=0; i<usersSize; i++)
    {
        if(isUpdated[i])
        {
            users[i]->giveDestinationRating(name);
        }
        else
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
            //std::cout<<"users after file"<<usersSize<<std::endl;
            iFile.read((char*)&dest,sizeof(int));
            for(int i=0; i<friends; i++)
            {

            }
            usersCapacity=usersSize+5;
            //std::cout<<usersSize<<std::endl;
            FileUser*users=new FileUser[usersSize];
            // iFile.seekg(sizeof(int),std::ios::beg);
            iFile.read((char*)users,(sizeof(FileUser)*usersSize));
            if(users==NULL)
            {
                iFile.close();
                throw MyException("Can not read database");
            }
            iFile.close();
        }

    }
}
}*/



