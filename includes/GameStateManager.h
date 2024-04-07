#pragma once

#include <map>
#include <string>
#include "GameState.h"

class GameStateManager
{
 
    std::map<int, GameState*> states;
    int current_state;

  public:
    GameStateManager()  
    {
    }

    virtual ~GameStateManager()
    {
    }

    virtual void AddState(int state_id, GameState* object);
    virtual void RemoveState(int state_id);
    virtual void SetState(int state_id);

    virtual void Update(float elapsed);
    virtual void Render();
};