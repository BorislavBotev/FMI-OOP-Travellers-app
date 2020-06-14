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
    desArchive->collectAllData();
    usArchive->collectAllData();
    homepage();
    usArchive->updateUserInDB(*user);
    desArchive->updateFile();
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
        std::cout<<"1-View all destinations\t2-View your destinations\t3-View your friendlist\t4-Add friend\t5-Add Destination"<<std::endl;
        std::cin>>command;
        std::cin.ignore();
        switch(command)
        {
        case 1:
            desArchive->printDestinations();
            break;
        case 2:
            user->viewMyDestinations();
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
        case 5:
        {
            try
            {
                desArchive->addDestination(user->addDestination());
            }
            catch(MyException e)
            {
                std::cout<<e.what()<<std::endl;
            }

            break;
            case -1:
                return ;
            default:
                std::cout<<"Please write valid command"<<std::endl;
                break;
            }

        }
    }
}


