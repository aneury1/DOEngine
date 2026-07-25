

#include "Application.h"
#include "StringUtils.h"
#include "DraggableGameObject.h"
#include "Event.h"
#include "FontCache.h"
#include "GameState.h"
#include "Logger.h"
#include "Mouse.h"
#include "SelectionRect.h"
#include "SpriteOffset.h"
#include "TTFText.h"
#include "Texture.h"
#include "Tile.h"
#include "Tilemap.h"
#include "UI.h"
#include "TextField.h"
#include "TileMapEditor.h"
#include "Utils.h"
#include "GameObject.h"
#include "MessageBox.h"
#include "DOEngine_SDL_includes.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>

enum State
{
    playing = 0
};


struct IntroGameState : public doengine::GameState{
    virtual void OnEnter(){}
    virtual void OnExit(){}
    virtual void Update(float elapsed){}
    virtual void Render(){}
};


int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    auto resoltion = doengine::Application::getApplication()->getDisplayMode(0);
    doengine::Rect rect{1320, 900};
    app->createWindow(rect);
    auto playstate = std::make_shared<IntroGameState>();
    app->addState(playstate, playing);
    app->setState(playing);

    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->clearScreen(doengine::Colors::black);
        app->Render();
    }
    app->Quit();
    return 0;
}