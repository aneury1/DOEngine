#pragma once

#include "GameState.h"
#include <map>
#include <string>
namespace doengine
{

class GameState;
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
} // namespace doengine