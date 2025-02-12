
#include "Application.h"
#include "Event.h"
#include "EventHandler.h"
#include "GameState.h"
#include "MusicHandler.h"
#include "SDLSoundHandler.h"
#include <algorithm>
#include <memory>
#include <string>

using doengine::SDLSoundHandler;

class MusicState : public doengine::GameState
{
  public:
    virtual void OnEnter()
    {
        timeInSecs = 90;

        auto app = doengine::Application::getApplication();

        const std::string TRACK_NAME_1 = "assets/sounds/Kick-Drum-1.wav";
        const std::string TRACK_NAME_2 = "assets/sounds/Snare-Drum-1.wav";

        soundHandler = new SDLSoundHandler;
        soundHandler->addToList(TRACK_NAME_1);
        soundHandler->addToList(TRACK_NAME_2);

        soundHandler->setRepeat(doengine::MusicHandler::Repeat::OnlyThis);

        soundHandler->setChannel(0);
        soundHandler->playFirst();
        soundHandler->setChannel(1);
        soundHandler->playLast();
    }
    virtual void OnExit()
    {
        SDL_Log("Exiting\n");
        delete soundHandler;
        soundHandler = nullptr;
        SDL_Quit();
    }
    virtual void Update(float elapsed)
    {
        auto app = doengine::Application::getApplication();
        SDL_Log("Time elapsed %ld\n", app->getElapsedTime());

        SDL_Log("Time remaining %ld\n", timeInSecs);

        if (timeInSecs-- <= 0)
        {
            soundHandler->stop(-1);
            app->Quit();
        }

        SDL_Delay(1000);
    }
    virtual void Render()
    {
    }

  private:
    SDLSoundHandler* soundHandler;
    unsigned long timeInSecs;
};

enum SampleStateId : int
{
    soundStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    // app->setSize(800, 600);
    auto soundState = new MusicState();
    app->addState(soundState, soundStateID);
    app->setState(soundStateID);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}
