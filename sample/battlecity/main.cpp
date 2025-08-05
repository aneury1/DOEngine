

#include <GameState.h>
#include <Renderer.h>
#include <Application.h>
#include <Event.h>
#include <SDL2/SDL.h>

#include "PlayStateMachine.h"

enum SampleStateId : int
{
    pongStateID = 1
};
#include <iostream>
int main(int argc, char* argv[])
{

    auto app = doengine::Application::getApplication();
    doengine::Rect rect{1800,900};
    app->createWindow(rect);
    auto pongState = new PlayStateMachine();
    app->addState(pongState, pongStateID);
    app->setState(pongStateID);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}
