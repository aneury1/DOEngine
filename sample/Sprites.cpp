
#include "Application.h"
#include "Event.h"
#include "EventHandler.h"
#include "GameState.h"
#include "Sprite.h"
#include <algorithm>
#include <memory>
#include <string>

#include "DOEngine_SDL_includes.h"

class SpriteState : public doengine::GameState
{
  public:
    virtual void OnEnter()
    {
        timeInSecs = 90;

        auto app = doengine::Application::getApplication();
    }
    virtual void OnExit()
    {
        SDL_Log("Exiting\n");
        SDL_Quit();
    }
    virtual void Update(float elapsed)
    {
        auto app = doengine::Application::getApplication();
        SDL_Log("Time elapsed %ld\n", app->getElapsedTime());

        SDL_Log("Time remaining %ld\n", timeInSecs);

        if (timeInSecs-- <= 0)
        {
            app->Quit();
        }

        SDL_Delay(1000);
    }
    virtual void Render()
    {
    }

  private:
    unsigned long timeInSecs;
};

enum SampleStateId : int
{
    SpriteStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    // app->setSize(800, 600);
    auto spriteState = new SpriteState();
    SampleStateId spriteStateID = SampleStateId::SpriteStateID;
    app->addState(spriteState, spriteStateID);
    app->setState(spriteStateID);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}
