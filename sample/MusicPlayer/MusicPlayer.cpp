
#include "Application.h"
#include "Grids.h"
#include "TTFText.h"
#include <Event.h>
#include <GameState.h>
#include "DOEngine_SDL_includes.h"
#include <atomic>
#include <complex>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <vector>
using namespace doengine;

const std::vector<std::string> music = {
    "PLAY TESTgi"
};





struct MusicPlayerState : public doengine::GameState
{
  
    Renderer* renderer;
    TTFText*  text;
    
    Texture* ps = nullptr;
    Texture* parcial = nullptr;
    Texture* fontRenderer = nullptr;
    
    virtual void OnEnter()
    {
         renderer = Application::getApplication()->getRender();
        
       /// ps = new Texture("./assets/gfx/ball.bmp");
       /// ps->SetTransparentColor(black);
      ///  parcial = ps->subTexture(Rect{20,10,10,10});
        text =new TTFText();
       /// text->setFont("./assets/fonts/DroidSans.ttf", 23);
        fontRenderer = text->createBitmapFont("./assets/fonts/DroidSans.ttf",
         doengine::Colors::yellow, 
         doengine::Colors::red);
    }
    virtual void OnExit()
    {
    }
    int inc = 32;
    virtual void Update(float elapsed)
    {
        if(Event::getLastKeyPressed(SDL_SCANCODE_0))
           inc++;
        
        if(Event::getLastKeyPressed(SDL_SCANCODE_1))
           inc--;
 
    }
    virtual void Render()
    {
       renderer->setDrawColor(doengine::Colors::skyBlue);
       renderer->clear();
       // ps->Draw(Rect{100,100,100,100});
       // parcial->Draw(Rect{10,10,100,100});

       /// ps->Draw(Rect{100,100,100,100},Rect{10,10,inc,inc});
       /// fontRenderer->Draw(Rect{100,100,100,100});
       text->DrawText("HOLAAAAAA", 10,10);
    }
};

enum SampleStateId : int
{
    MuscPlayerStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{400,400};
    app->createWindow(rect);
    auto MuscPlayerState = new MusicPlayerState();
    app->addState(MuscPlayerState, MuscPlayerStateID);
    app->setState(MuscPlayerStateID);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}
