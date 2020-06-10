#include <iostream>
#include "Application.hpp"
#include "TimePeriod.hpp"
#include "Photo.hpp"
#include "MyException.hpp"
#include "UsersArchive.hpp"
int main()
{

    /*const int MAX_PHOTOS=5;
    char input[50]= {};
    int count=0;

    while(count<MAX_PHOTOS)
    {
        Photo*p=NULL;
        std::cout<<"Enter file name for your photo"<<std::endl;
        std::cin.getline(input,50);
        if(strcmp(input,"-1")==0){break;}
        try
        {
            p=new Photo(input);
            count++;
        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
            delete p;
        }
    }
    /*char input[50];
    TimePeriod*t=new TimePeriod();
    while(true)
    {
        std::cout<<"Enter starting date:"<<std::endl;
        std::cin.getline(input,50);
        try
        {
            t->setFrom(input);
            break;
        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
        }
    }
    while(true)
    {
        std::cout<<"Enter ending date:"<<std::endl;
        std::cin.getline(input,50);
        try
        {
            t->setTill(input);
            break;

        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
        }
    }
    cout<<*t;*/
   while(true){
    Application* app=new Application();
    app->app();
    delete app;
    }
}
