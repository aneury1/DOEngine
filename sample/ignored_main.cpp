#include "Application.h"

#include "Application.h"
#include <GameState.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

struct PongState : public doengine::GameState
{
    virtual void OnEnter()
    {
    }
    virtual void OnExit()
    {
    }
    virtual void Update(float elapsed)
    {
    }
    virtual void Render()
    {
    }
};


enum SampleStateId : int
{
    pongStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    app->setSize(800, 600);
    doengine::Rect rect{800,600};
    app->createWindow(rect);
    auto pongState = new PongState();
    app->addState(pongState, pongStateID);
    app->setState(pongStateID);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Render();
    }
    app->Quit();
    return 0;
}
