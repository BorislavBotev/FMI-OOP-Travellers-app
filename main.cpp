#include <iostream>
#include "Application.hpp"
#include "TimePeriod.hpp"
#include "Photo.hpp"
#include "MyException.hpp"
#include "UsersArchive.hpp"
int main()
{
  while(true){
    Application* app=new Application();
    app->app();
    delete app;
    }
}

