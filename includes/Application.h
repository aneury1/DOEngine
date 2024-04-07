#pragma once 

#include <memory>
extern "C" {
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
}

#include "FPSManager.h"
#include "GameStateManager.h"
#include "Texture.h"
#include "Canvas.h"

class GameStateManager;

class Application 
{
    SDL_Window   *window;
    doengine::gfx::Renderer* render;
    SDL_Rect      window_rect;
    SDL_DisplayMode mode;
    std::shared_ptr<FpsManager> fps_handler;
    std::shared_ptr<GameStateManager> gsm;
    bool run;
    bool dirty;

   static Application *applicationObject;
    Application();
    ~Application();
 
   void _internalResize(){
    
      SDL_SetWindowSize(window, window_rect.w, window_rect.h);
    }

    public:

    static Application* getApplication(){
        if(applicationObject==nullptr)
            applicationObject = new Application();
        return applicationObject;
    }

    const bool    IsRunning() const;
    doengine::gfx::Renderer* getRender() const  {return render;}
    SDL_Window   *getWindow() {return window;}
   
    
    void setFullScreen();
    void setWindowMode();
   
    void PollEvent();
    void  Update();
    void  Render();
    void  Quit();
  
    void setW(int w){
       window_rect.w = w;
      _internalResize();
    }
    void setH(int h){
        window_rect.h = h;
        _internalResize();
    }
    void setSize(int w, int h){
        window_rect.w = w;
        window_rect.h = h;
       _internalResize();
    }
    int getH()  {
        return window_rect.h;
    }
    int getW()  {
        return window_rect.w;
    }

    void SetWindowPencilColor(doengine::Color color);

    void addState(GameState *state, int id){
        gsm->AddState(id,state);
    }

    void setState(int id){
        gsm->SetState(id);
    }

    private:
    void destroy();
};