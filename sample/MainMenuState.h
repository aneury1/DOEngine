#pragma once
#include <Canvas.h>
#include <GameState.h>

class MainMenuState : public GameState
{

  public:
    MainMenuState(Window* w) : GameState(w)
    {
    }
    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float elapsed);
    virtual void Render();
};