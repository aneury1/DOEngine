#pragma once 


#include "StateMachine.h"


class DevState: public GameState{
    public:
  DevState(){}
  virtual ~DevState(){}
  virtual void onEnter();
  virtual void onExit();
  virtual void Update();
  virtual void Render();
private:
	SDL_Joystick* joy;
	SDL_Event ev;
};