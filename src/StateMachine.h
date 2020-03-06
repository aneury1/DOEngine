#pragma once
#include <SDL.h>
#include <map>
#include "Event.h" 



class GameState
{
  protected:
  public:
  
  GameState(){}
  virtual ~GameState(){}
  virtual void onEnter()=0;
  virtual void onExit()=0;
  virtual void Update()=0;
  virtual void Render()=0;
};

enum{
    ARKANOID_STATE, 
    DOODLE_JUMP,
    SNAKE_STATE,


    TOTAL_STATE_LOADED
};


class GameStateMachine{
   std::map<int, GameState*>states;
   int current_state;

public:  
    GameStateMachine(){
        current_state = -1;
    }
    void addState(int state_id, GameState *game);
    void removeState(int state_id);
    void setState(int state_id);

    void Update();
    void Render();

 };