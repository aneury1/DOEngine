
#include "Application.h"
#include "GameState.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>

class PongState : public doengine::GameState
{
  public:
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
