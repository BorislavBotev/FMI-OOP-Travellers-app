#include "DestinationsArchive.hpp"
DestinationsArchive::DestinationsArchive()
{
    destinationsCapacity=0;
    destinationsSize=0;
    fDestinations=NULL;
    isFileUpdated=true;
}
DestinationsArchive::~DestinationsArchive()
{
    delete[] fDestinations;
}


void DestinationsArchive::collectAllData()
{
    std::ifstream iFile(DES_ARCHIVE_NAME[0],std::ios::binary);
    if(iFile.bad())
    {
        iFile.close();
        throw MyException("Can not open file");
    }
    destinationsSize=0;
    destinationsCapacity=destinationsSize+5;
    iFile.read((char*)&destinationsSize,sizeof(int));
    FileDestination*fDestinations=new FileDestination[destinationsCapacity];
    iFile.read((char*)fDestinations,(sizeof(FileDestination)*destinationsSize));
    if(fDestinations==NULL)
    {
        iFile.close();
        throw MyException("Can not read file");
    }
    iFile.close();
}
void DestinationsArchive::addDestination(char*name)
{
    if(!name)
    {
        return;
    }
    for(int i=0; i<destinationsSize; i++)
    {
        if(strcmp(fDestinations[i].name,name)==0)
        {
            return;
        }
    }
    if(destinationsSize==destinationsCapacity)
    {
        destinationsCapacity*=2;
        FileDestination*arr=new FileDestination[destinationsCapacity];
        for(int i=0; i<destinationsSize; i++)
        {
            arr[i]=fDestinations[i];
        }
        arr[destinationsSize++]=FileDestination(name);
        delete[]fDestinations;
        fDestinations=arr;
    }
    else
    {
        fDestinations[destinationsSize++]=FileDestination(name);
    }
    isFileUpdated=false;
}

void DestinationsArchive::updateFile()
{
    if(!isFileUpdated)
    {
        std::ofstream oFile(DES_ARCHIVE_NAME[0],std::ios::binary);
        if(!oFile.is_open())
        {
            throw MyException("Can not open file");
        }
        oFile.seekp(0);
        oFile.write((char const*)&destinationsSize,sizeof(int));
        for(int i=0; i<destinationsSize; i++)
        {
            oFile.write((char const*)&fDestinations[i],sizeof(FileDestination));
        }
        oFile.close();
    }
}

/*FileDestination* DestinationsArchive:: downloadDestinations()
{
    std::ifstream iFile("destinations.db",std::ios::binary);
    if(iFile.bad())
    {
        iFile.close();
        throw MyException("Can not open file");
    }
    iFile.read((char*)&destinationsSize,sizeof(int));
    //std::cout<<"users after file"<<usersSize<<std::endl;

    if(destinationsSize==0)
    {
        return NULL;
    }
    destinationsCapacity=destinationsSize+5;
    //std::cout<<usersSize<<std::endl;
    FileDestination*des=new FileDestination[destinationsSize];
    // iFile.seekg(sizeof(int),std::ios::beg);
    iFile.read((char*)des,(sizeof(FileUser)*destinationsSize));
    if(des==NULL)
    {
        iFile.close();
        throw MyException("Can not read database");
    }
    iFile.close();
    return des;
}
*/
void DestinationsArchive::printDestinations()
{
    if(destinationsSize==0)
    {
        std::cout<<"There are no destinations"<<std::endl;
        return;
    }
    for(int i=0; i<destinationsSize; i++)
    {
        std::cout<<i+1<<"-"<<fDestinations[i].name<<std::endl;
    }
}
/*
FileDestination& DestinationsArchive::viewDestinations(int& command)
{
    if(destinationsSize==0)
    {
        std::cout<<"There are no destinations"<<std::endl;
        return;
    }
    while(true)
    {
        printDestinations();
        std::cout<<"Choose destination for more rating info or 0 to go back"<<std::endl;
        std::cin>>command;
        if(command==0 || command==-1)
        {
            return NULL;
        }
        else if(command>=1 && command<=destinationsSize)
        {
            //std::cout<<destinations[command-1].name<<" "<<destinations[command-1].rating<<std::endl;
            return fDestinations[i];
        }
        else
        {
            std::cout<<"Invalid command"<<std::endl;
        }
    }
}

void  DestinationsArchive::viewDestinationsRatings(const char*name)
{
   /* FileUser*users=downloadUsers();
    for(int i=0; i<countUsers; i++)
    {
        std::ifstream o(users[i].name,std::ios::binary);
        int usersDestinations=0;
        o.read((char*)usersDestinations,sizeof(int));
        UserDestinations*destinations=new UserDestinations[usersDestinations];
        o.read((char*)destinations,sizeof(UserDestinations));
        for(int j=0; j<usersDestinations; j++)
        {
            if(strcmp(destination.name,destinations[j].name))
            {
                std::cout<<users[i].name<<" "<<destinations[j].rating<<std::endl;
            }
        }
        delete[] destinations;

    }
    delete[] users;
    std::cout<<"Press 0 to go back"<<std::endl;
    std::cin>>command;
    while(command!=0)
    {
        std::cin>>command;
    }*/
//}
