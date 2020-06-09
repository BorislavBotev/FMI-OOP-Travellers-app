#include "Application.hpp"
Application::Application()
{
    user=NULL;
    command=0;
    usArchive=new UsersArchive();
    desArchive=new DestinationsArchive();
}

Application::~Application()
{
    delete user;
    delete usArchive;
    delete desArchive;
}

void Application:: app()
{
        logIn();

        std::cout<<"Lets go"<<std::endl;
        usArchive->collectAllData();
        homepage();
        usArchive->updateUserInDB(*user);
       // delete user;

}

void Application::logIn()
{
    std::cout<<"Welcome! You can always leave with the -1 command! Have fun!!"<<std::endl;
    while(true)
    {
        std::cout<<"1-Sign in\t2-Register\t3-See all registered users"<<std::endl;
        std::cin>>command;
        std::cin.ignore();
        switch(command)
        {
        case 1:
            try
            {
                user=usArchive->signIn();
            }
            catch(MyException e)
            {
                std::cout<<e.what()<<std::endl;
                break;
            }
            return ;
        case 2:
            try
            {
                user=usArchive->registerUser();
                std::cout<<"WOW"<<std::endl;

            }
            catch(MyException e)
            {
                std::cout<<e.what()<<std::endl;
                break;
            }
            return ;
        case 3:
            usArchive->printUsers();
            break;
        case -1:
            return ;
        default:
            std::cout<<"Please write valid command"<<std::endl;
            break;
        }
    }
}

void Application::homepage()
{
    while(true)
    {
        std::cout<<"1-View all destinations\t2-View your destinations\t3-View your friendlist\t4-Add friend"<<std::endl;
        std::cin>>command;
        std::cin.ignore();
        switch(command)
        {
        case 1:
            /*FileDestination*fd=desArchive->viewDestinations(command);
            if(fd!=NULL)
            {
                usArchive->userInfoForDestination(fd->name);
            }*/
            break;
        case 2:
            // viewMyDestinations();
            break;
        case 3:
            user->viewFriends();
            break;
        case 4:
            std::cout<<"Name: ";
            char username[MAX_NAME_LENGTH];
            std::cin.getline(username,MAX_NAME_LENGTH);
            if(!usArchive->isNameValidUser(username))
            {
                std::cout<<"There is no such user"<<std::endl;
                break;
            }
            user->addFriendWtihValidation(username);
            break;
        case 0:
            return;
        case -1:
            return ;
        default:
            std::cout<<"Please write valid command"<<std::endl;
            break;
        }

    }
}

/*void Application::viewDestinations()
{
    std::ifstream iFile("destinations.db",std::ios::binary);
    iFile.read((char*)countDestinations,sizeof(int));
    if(countDestinations==0)
    {
        std::cout<<"There are no destinations added"<<std::endl;
        return;
    }
    FileDestination*destinations=new FileDestination[countDestinations];
    iFile.read((char*)destinations,sizeof(FileDestination)*countDestinations);
    while(true)
    {
        printDestinations(destinations);
        std::cout<<"Choose destination for more rating info or 0 to go back"<<std::endl;
        std::cin>>command;

        if(command!=0)
        {
            break;
        }
        else
        {
            std::cout<<destinations[command-1].name<<" "<<destinations[command-1].rating<<std::endl;
            viewDestinationsRatings(destinations[command-1]);
        }
    }
    delete[] destinations;

}

void  Application::viewDestinationsRatings(FileDestination& destination)
{
    FileUser*users=downloadUsers();
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
    }
}


void Application::printDestinations(FileDestination* destinations)
{
    for(int i=0; i<countDestinations; i++)
    {
        std::cout<<i+1<<"-"<<destinations[i].name<<", Rating:"<<destinations[i].rating<<std::endl;
    }
}*/


