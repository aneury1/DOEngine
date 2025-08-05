#ifndef PLAYSTATE_MACHINE_H_DEFINED
#define PLAYSTATE_MACHINE_H_DEFINED
#include <GameState.h>
#include <Renderer.h>
#include <Application.h>
#include <Event.h>
#include <TileMap.h>
#include <SDL2/SDL.h>

struct PlayStateMachine : public doengine::GameState
{
    doengine::Renderer *render;
    doengine::TileMap* map;
    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float elapsed);
    virtual void Render();
};


#endif