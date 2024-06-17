
#pragma once
#include <GameState.h>

class TileMapTestState : public GameState, KeyDownEvent
{

  public:
    TileMapTestState(Window* w) : GameState(w)
    {
    }
    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float elapsed);
    virtual void Render();
    virtual void OnKeydown(int code);
};