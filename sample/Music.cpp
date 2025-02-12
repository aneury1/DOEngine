
#include "Application.h"
#include "Event.h"
#include "EventHandler.h"
#include "GameState.h"
#include "Geometric.h"
#include "Keyboard.h"
#include "MusicHandler.h"
#include "SDLMusicHandler.h"
#include <algorithm>
#include <memory>
#include <string>

using namespace doengine;

class MusicState : public GameState, public KeyDownEvent
{
  public:
    virtual void OnEnter()
    {
        timeInSecs = 90;
        musicNum = 0;

        auto app = doengine::Application::getApplication();
        doengine::Event::AddKeyPressEventListener(this);

        const std::string MUSIC_NAME_1 =
            "assets/sounds/gymnopedie-1-erik-satie.mp3";
        const std::string MUSIC_NAME_2 = "assets/sounds/flat-8-bit.mp3";

        musicHandler = new SDLMusicHandler;
        musicHandler->addToList(MUSIC_NAME_1);
        musicNum++;
        nextIndexMusic = musicHandler->addToList(MUSIC_NAME_2);
        musicNum++;
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
            // musicHandler->stop();
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

        switch (static_cast<devices::Keycode>(keyboard.getLastKeyPressed()))
        {
        case devices::Keycode::KeyP:
            musicHandler->pause(nextIndexMusic);
            break;
        case devices::Keycode::KeyUp:
            nextIndexMusic = (nextIndexMusic - 1) % musicNum;
            break;
        case devices::Keycode::KeyDown:
            nextIndexMusic = (nextIndexMusic + 1) % musicNum;
            break;
        case devices::Keycode::KeyR:
            musicHandler->playIndex(nextIndexMusic);
            break;
        case devices::Keycode::KeyQ:
            SDL_Log("Quitting...");
            Application::getApplication()->Quit();
            break;
        }
    }

  private:
    SDLMusicHandler* musicHandler;
    unsigned long timeInSecs;
    unsigned short nextIndexMusic;
    size_t musicNum;
};

enum SampleStateId : int
{
    pongStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = Application::getApplication();
    app->createWindow(Rect{800, 600});
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
