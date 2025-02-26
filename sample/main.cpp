#include "Application.h"
#include <GameState.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
 
int main(int argc, char* argv[])
{
    #if 0 
    auto app = Application::getApplication();
    app->setSize(800, 600);
    auto pongState = new SampleState();
    app->addState(pongState, pongStateID);
    app->setState(pongStateID);
    while (app->IsRunning())
    {
        app->PollEvent();

        app->Render();
    }
    app->Quit();
    #endif
    return 0;
}