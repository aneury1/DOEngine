#pragma once 
#include "GameState.h"
#include "Event.h"
#include "EventHandler.h"

class PlatformState: public GameState, MouseEvent
{
    public:
   PlatformState(Window *w):GameState(w){}
   virtual void OnEnter();
   virtual void OnExit();
   virtual void Update(float elapsed);
   virtual void Render();


   virtual void MouseMove(int x, int y)override;

   virtual void MouseButtonDown(int which){}
   
   virtual void MouseButtonUp(int which){}
    
};