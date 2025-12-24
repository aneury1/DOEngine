

#include "Application.h"
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
#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "MessageBox.h"
#include "Sprite.h"
#include "Utils.h"



 
struct Player : 
    public doengine::KeyboardInputhandlingEvent
{
   doengine::Application *app;
   doengine::Renderer *renderer;
   doengine::Rect offset;
   double speedx   = 0;
   double speedy   = 0;
   bool is_jumping = false;
   
   Player();

   void Update(double elapsed);
   
   void Render();
   
   virtual void OnKeydown(const Keyboard& keyboard)
   {
        doengine::LogOuput(
            doengine::logger_type::Information,
            "Key pressed %d", keyboard.getLastKeyPressed()
        );
   }
   
   virtual void OnKeyup(const Keyboard& keyboard)
   {

   }
};

Player::Player()
{
    app = doengine::Application::getApplication();
    renderer = app->getRender();
    this->offset.x = 10;
    offset.h = 200;
    offset.w = 200;
    this->offset.y = app->getH() - offset.h;
}

void Player::Update(double elapsed)
{
}
void Player::Render()
{
    renderer->DrawFillRect(offset, doengine::Colors::white); 
}


struct Background {};



struct Enemy {};
 
struct PlayState : public doengine::GameState
{
    doengine::TextureManager *textureManager;
    Player *player;
  
    void createInstance()
    {
        textureManager = doengine::TextureManager::getTextureManager();
        player = new Player();
    }
    void loadTextures()
    {
        textureManager->loadTextureFromFile("player", "./assets/gfx/sprites/player.png");
        textureManager->loadTextureFromFile("enemy", "./assets/gfx/sprites/enemy_1.png");
        textureManager->loadTextureFromFile("bg", "./assets/background/background_single.png");
    }

    virtual void OnEnter()
    {
        createInstance();
        loadTextures();
    }
    virtual void OnExit() {}
    virtual void Update(float elapsed) 
    {
        player->Update(elapsed);
    }
    virtual void Render()
    {
        drawLayer1();
        drawLayer2();
        drawLayer3();
    }
    void drawLayer1()
    {
        textureManager->getTexture("bg")->Draw({0,0,800, 600});
    }
    void drawLayer2()
    {

    }
    void drawLayer3()
    {
        player->Render();
    }
};



int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    auto resoltion = doengine::Application::getApplication()->getDisplayMode(0);
    doengine::Rect rect{800, 600};
    app->createWindow(rect);
    auto playstate = new PlayState();
    app->addState(playstate, 1);
    app->setState(1);

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


