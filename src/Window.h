#pragma once
#include <SDL.h>
#include <memory>
#include "StateMachine.h"
#include "Event.h" 

#include "Texture.h"

class Sprite;

class Window
{
   bool enable_opengl;
   SDL_Window   *window;
   SDL_Renderer *render;
   SDL_Rect      window_rect;
   GameStateMachine* gsm;
   bool running;

   public:

   Window(int w, int h, const char *title );
   ~Window();
   bool isRunning();
   void setClearColor(Uint8 r, Uint8 g, Uint8 b);
   void Clear();
   void UpdateScreen();
   void PollEvent( );
   SDL_Renderer *getRender(){return render;}
   void addState(int state_id, GameState *ptr){
       gsm->addState(state_id, ptr);
   }
   void Quit(){
       running =false;
   }
  SDL_Rect getWindowRect(){return window_rect;}
  int getWidth(){return window_rect.w;}
   int getHeight(){return window_rect.h;}
  inline GameStateMachine* getGSM(){
      return gsm;
  }

  int getScaleFactor(){
      return (int)window_rect.h/window_rect.w;
  }

  inline void addKeyListener(KeyboardObserver *observer){
       Event::getEventHandler()->addKeyboardObserver(observer);
   }

   void DrawSprite(Sprite* sprite);


};
extern Window *window;