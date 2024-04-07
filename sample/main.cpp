
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "Application.h"

int main(int argc, char* argv[])
{ 
   auto app = Application::getApplication();
   
   app->setSize(800, 600);

    while(app->isRunning()){
        app->PollEvent();

        app->Render();
    }
    app->Quit();
    return 0;
}
