#include "GameObject.h"
#include "MessageBox.h"
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


using doengine::Application;
using doengine::Rect;
using doengine::Renderer;
using doengine::GameState;
using doengine::SpriteAnimationOffset;
using doengine::Color;
using doengine::KeyDownEvent;
using doengine::MouseEvent;
using doengine::KeyboardInputhandlingEvent;
using doengine::TextInputEvent;
using doengine::TileMapEditor;
using doengine::TileMap;
using doengine::NonScrollCharTileMap;
using doengine::TextureManager;
using doengine::TileCharTextureOffset;
using doengine::TileDef;
using doengine::Texture;
using doengine::SelectionRect;
using doengine::GameObject;
using doengine::checkCollision;



struct BattleCityMainPlayer : 
 public GameObject//,
 /////public KeyboardInputhandlingEvent
{
    virtual void Update(float timer = 0);
    virtual void Render();
    virtual bool isColliding(GameObject* other);
};

void BattleCityMainPlayer::Update(float timer)
{

}

void BattleCityMainPlayer::Render()
{

}

bool BattleCityMainPlayer::isColliding(GameObject* other)
{
    return false;
}




struct PlayState : 
    public GameState,
    public KeyboardInputhandlingEvent
{

    NonScrollCharTileMap* tilemap;
    Texture* texture;
    SelectionRect *helperSelection;

    /// Player
    BattleCityMainPlayer *player;
    
    void loadTileMapResource();
    void loadDebugResource();


    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float elapsed);
    virtual void Render();
    virtual void OnKeydown(const Keyboard&);
    virtual void OnKeyup(const Keyboard&);
};

void PlayState::loadDebugResource()
{
   helperSelection = new SelectionRect();
   helperSelection->setFont("./assets/fonts/DroidSans.ttf");
   helperSelection->setFontColor(doengine::Colors::red);
}

void PlayState::loadTileMapResource()
{
   tilemap = new NonScrollCharTileMap();
   TextureManager::getTextureManager()->loadTextureFromFile("battle_city_sprites", "/home/neonland/Documents/DOEngine/assets/gfx/sprites/battle_city.jpg");
   tilemap->loadTileMapFromFile("./assets/maps/testmap.map");
   tilemap->setTileSetId("battle_city_sprites");
   texture = TextureManager::getTextureManager()->getTexture("battle_city_sprites");
   std::unordered_map<char, TileCharTextureOffset> battleCitySpriteSheet1
    {
        {'b', {'b', doengine::Rect{257, 00, 15, 15}}},
        {'w', {'w', doengine::Rect{257, 17, 15, 15}}},
        {'g', {'g', doengine::Rect{257, 36, 15, 15}}},
        {'B', {'B', doengine::Rect{257, 49, 15, 15}}},
        {'M', {'M', doengine::Rect{257, 97, 15, 15}}},
        {'C', {'C', doengine::Rect{273, 33, 15, 15}}},
        {'s', {'s', doengine::Rect{289, 33, 15, 15}}},
        {'t', {'t', doengine::Rect{259, 42, 15, 15}}},
    };
    std::unordered_map<char, TileDef> defs;
    for(auto it : battleCitySpriteSheet1)
    {
        defs[it.first] = doengine::TileDef();
        defs[it.first].layer = 0;
        defs[it.first].src   = it.second.offset;
        defs[it.first].textureId = "battle_city_sprites";
    }
    tilemap->setTileDef(defs);
}

void PlayState::OnEnter()
{
    loadTileMapResource();
    loadDebugResource();

    player = new BattleCityMainPlayer();

}
void PlayState::OnExit()
{

}
void PlayState::Update(float elapsed)
{

    player->Update(elapsed);
}
void PlayState::Render()
{
   tilemap->Draw();
   ///texture->Draw({0,0,texture->getWidth(),texture->getHeight()});
   ///helperSelection->render(nullptr);
   player->Render();
}
void PlayState::OnKeydown(const Keyboard&)
{

}
void PlayState::OnKeyup(const Keyboard&)
{

}


int main(int argc, char *argv[])
{
    auto app = doengine::Application::getApplication();
    auto resoltion = doengine::Application::getApplication()->getDisplayMode(0);
    doengine::Rect rect{resoltion.w/2, resoltion.h};
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
    return 0;
}


