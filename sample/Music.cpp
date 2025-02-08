
#include "Application.h"
#include "Event.h"
#include "EventHandler.h"
#include "GameState.h"
#include "MusicHandler.h"
#include "SDLMusicHandler.h"
#include <algorithm>
#include <memory>
#include <string>

using doengine::devices::SDLMusicHandler;

class MusicState : public doengine::GameState, public doengine::KeyDownEvent
{
  public:
    virtual void OnEnter()
    {
        timeInSecs = 90;

        auto app = doengine::Application::getApplication();
        doengine::Event::AddKeyPressEventListener(this);

        const std::string MUSIC_NAME =
            "assets/sounds/gymnopedie-1-erik-satie.mp3";
        musicHandler = new SDLMusicHandler;
        musicHandler->addToList(MUSIC_NAME);
        musicHandler->setRepeat(doengine::MusicHandler::Repeat::OnlyThis);
        musicHandler->playFirst();
    }
    virtual void OnExit()
    {
        SDL_Log("Exiting\n");
        delete musicHandler;
        musicHandler = nullptr;
        SDL_Quit();
    }
    virtual void Update(float elapsed)
    {
        auto app = doengine::Application::getApplication();
        SDL_Log("Time elapsed %ld\n", app->getElapsedTime());

        SDL_Log("Time remaining %ld\n", timeInSecs);

        if (timeInSecs-- <= 0)
        {
            //musicHandler->stop();
            app->Quit();
        }

        SDL_Delay(1000);
    }
    virtual void Render()
    {
    }

    void OnKeydown(const Keyboard& keyboard) override
    {
        SDL_Log("Key %d pressed down", keyboard.getLastKeyPressed());
    }

  private:
    SDLMusicHandler* musicHandler;
    unsigned long timeInSecs;
};

enum SampleStateId : int
{
    pongStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    // app->setSize(800, 600);
    auto pongState = new MusicState();
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
