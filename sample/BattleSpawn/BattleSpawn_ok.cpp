

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
#include "DOEngine_SDL_includes.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "MessageBox.h"


enum State
{
    playing = 0
};
const std::string sprite =
    "/home/neon/Desktop/SimpleServer/DOEngine/assets/gfx/sprites/spriterpg.png";
const std::string fontsrc =
    "/home/neon/Desktop/SimpleServer/DOEngine/assets/fonts/NirmalaB.ttf";

enum class TextureId
{
    FontSpriteAtlas = 1
};

enum SpriteOffsetPosition
{
    FW,
    BW
};

doengine::SpriteAnimationOffset sampleSprite{FW,
                                    {
                                        {580 * 1, 0, 580, 532},
                                        {580 * 1, 0, 580, 532},
                                        {580 * 2, 0, 580, 532},
                                        {580 * 3, 0, 580, 532},
                                        {580 * 4, 0, 580, 532},
                                        {580 * 5, 0, 580, 532},
                                    }};





std::unordered_map<char, doengine::TileCharTextureOffset> battleCitySpriteSheet1
{
    {'b', {'b', doengine::Rect{45, 44, 123, 113}}},
    {'w', {'w', doengine::Rect{56, 401, 124, 103}}},
    {'g', {'g', doengine::Rect{49, 212, 135, 114}}},
    {'B', {'B', doengine::Rect{298, 219, 125, 112}}},
    {'M', {'M', doengine::Rect{530, 197, 220, 151}}},
    {'C', {'C', doengine::Rect{786, 196, 194, 138}}},
    {'s', {'s', doengine::Rect{786, 196, 194, 138}}},
    {'t', {'t', doengine::Rect{786, 196, 194, 138}}},
};


std::unordered_map<char, doengine::TileCharTextureOffset> battle_city_original_sheet
{
    {'b', {'b', doengine::Rect{256, 0, 15, 15}}},
    {'b', {'b', doengine::Rect{256, 0, 15, 15}}},
    {'b', {'b', doengine::Rect{256, 0, 15, 15}}},
    {'b', {'b', doengine::Rect{256, 0, 15, 15}}},
    {'b', {'b', doengine::Rect{256, 0, 15, 15}}},
    {'b', {'b', doengine::Rect{256, 0, 15, 15}}},

};




struct Player : 
    public doengine::GameObject, 
    public doengine::KeyboardInputhandlingEvent
{
    doengine::Rect playerPos;
    doengine::Color playerColor;
    doengine::Texture *sprite;
    
    Player()
    {

    }

    void setPlayerPosition(doengine::Rect pos)
    {
        playerPos = pos;
    }   
    
    virtual void Update(float timer = 0)
    {

    }
    virtual void Render()
    {

    }
 
    virtual void OnKeydown(const Keyboard& keyboard)
    {

    }
    virtual void OnKeyup(const Keyboard&)
    {

    }
};




struct PlayState : public doengine::GameState,
                   public doengine::KeyboardInputhandlingEvent,
                   public doengine::MouseEvent
{
    doengine::Renderer* renderer;

    doengine::SelectionRect recti;

    doengine::TileMapEditor* mapEditor;

    doengine::NonScrollCharTileMap *tilemap;
    
    doengine::TextField* field;

    doengine::MessageBox* msgBox;


    doengine::TTFText *textCoords;
    doengine::Rect clipped;

    PlayState()
    {
    }

    virtual ~PlayState()
    {
    }




    virtual void OnEnter()
    {
    
    
            doengine::TextureManager::getTextureManager()->loadTextureFromFile(
            "battle_city_sprites", 
            "./assets/gfx/sprites/battle_city.jpg");
        textCoords = new doengine::TTFText();
        textCoords->setFont("/home/neonland/Documents/DOEngine/build/assets/fonts/NirmalaB.ttf", 20);
        ////home/neonland/Documents/DOEngine/assets/fonts/NirmalaB.ttf
        recti.setFont("/home/neonland/Documents/DOEngine/build/assets/fonts/NirmalaB.ttf");
        renderer = doengine::Application::getApplication()->getRender();
        doengine::TextureManager::getTextureManager()->loadTextureFromFile(
            "sprite1", "/home/neonland/Pictures/shadow_dog.png");
        doengine::TextureManager::getTextureManager()->loadTextureFromFile(
            "save1", "./assets/gfx/save.png");
        doengine::TextureManager::getTextureManager()->loadTextureFromFile(
            "tileset1", "./assets/gfx/battle_city_tileset_1.png");
        mapEditor = new doengine::TileMapEditor("/home/neonland/Documents/DOEngine/build/assets/fonts/NirmalaB.ttf");
        mapEditor->setup("tileset1", battle_city_original_sheet);
        tilemap = new doengine::NonScrollCharTileMap();
        tilemap->loadTileMapFromFile("./assets/maps/testmap.map");
        tilemap->setTileMapEditor(mapEditor);
        std::unordered_map<char, doengine::TileDef> defs;
        for(auto it : battleCitySpriteSheet1)
        {
            defs[it.first] = doengine::TileDef();
            defs[it.first].layer = 0;
            defs[it.first].src   = it.second.offset;
            defs[it.first].textureId = "tileset1";
        }
        tilemap->setTileDef(defs);

        recti.registerSelectionRectFinished([this](doengine::Rect rect){
            tilemap->changeGroupOfTileByRectCollision(tilemap->getEditorType(), rect);
            clipped = rect;
        });
 
        msgBox = new doengine::MessageBox("QUIERES GUARDAR ESTO? ",
            "/home/neonland/Documents/DOEngine/build/assets/fonts/NirmalaB.ttf", 
            [this](int id){
                msgBox->hide();
            });

        textCoords->setForegroundColor(doengine::Colors::red);
    }

    void DrawLayer1()
    {
       
    }

    void DrawLayer2()
    {
        
    }

    void DrawLayer3()
    {
       tilemap->Draw();
      ////  mapEditor->render();
      //  
      /// auto battle_city_text = 
       ///doengine::TextureManager::getTextureManager()->getTexture("battle_city_sprites");
       ////battle_city_text->Draw({0,0, battle_city_text->getWidth()*2, battle_city_text->getHeight()*2});
      ////  if(!mapEditor->isVisible())
      ///rect.setFontColor(doengine::Colors::green);
      ///rect.render(renderer);
      ////
      /////   msgBox->render();

      ////textCoords->DrawText(300,600,"[%d, %d, %d %d]", clipped.x/2, clipped.y/2, clipped.w/2, clipped.h/2);
    }

    virtual void MouseMove(const Mouse& mouse)
    {
    }

    virtual void MouseButtonDown(const Mouse& mouse)
    {
    }

    virtual void MouseButtonUp(const Mouse& mouse)
    {
    }

    virtual void OnKeydown(const Keyboard& keyboard)
    {
    }

    virtual void OnKeyup(const Keyboard&)
    {
    }

    virtual void OnExit()
    {
    }

    virtual void Update(float elapsed)
    {
        tilemap->Update(elapsed);
    }

    virtual void Render()
    {
        DrawLayer1();
        DrawLayer2();
        DrawLayer3();
    }
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    auto resoltion = doengine::Application::getApplication()->getDisplayMode(0);
    doengine::Rect rect{resoltion.w, resoltion.h};
    app->createWindow(rect);
    auto playstate = new PlayState();
    app->addState(playstate, playing);
    app->setState(playing);

    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->clearScreen(doengine::Color(144, 240, 252, 255));
        app->Render();
    }
    app->Quit();
    return 0;
}
