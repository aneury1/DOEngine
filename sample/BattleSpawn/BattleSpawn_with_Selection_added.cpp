
#include <unordered_map>
#include "TTFText.h"
#include "Texture.h"
#include "Application.h"
#include "GameState.h"
#include "Mouse.h"
#include "UI.h"
#include "Event.h"
#include "Tile.h"
#include "TTFText.h"
#include <vector>
#include <SDL2/SDL.h>
#include "DraggableGameObject.h"
#include "SelectionRect.h"

enum State
{
   playing = 0
};
const std::string sprite = "/home/neon/Desktop/SimpleServer/DOEngine/assets/gfx/sprites/spriterpg.png";
const std::string fontsrc = "/home/neon/Desktop/SimpleServer/DOEngine/assets/fonts/NirmalaB.ttf";

enum class TextureId{
   FoodSpriteAtlas = 1
};

enum  SpriteOffset{
   Sandwich = 1,
   Bistec
};



std::unordered_map<int, doengine::Rect> spriteOffsets{
    { SpriteOffset::Sandwich , doengine::Rect{ 147, 17, 82, 48} },
    { SpriteOffset::Bistec   , doengine::Rect{ 186, 128, 55, 31} }
};




struct PlayState : 
    public doengine::GameState, 
    public doengine::KeyboardInputhandlingEvent,
    public doengine::MouseEvent
{
    
    std::vector<doengine::DraggableGameObject *> gamesamples;
    doengine::Texture *bg;
    doengine::Texture *stuff1;

  
    doengine::SelectionRect *selected;



    PlayState()
    {
        
    }
    
    virtual ~PlayState()
    {

    }
   
    doengine::Renderer* renderer;
   
    virtual void OnEnter()
    {
        renderer = doengine::Application::getApplication()->getRender();
        
        doengine::TextureManager::getTextureManager()->loadTextureFromFile(
            ((int)(TextureId::FoodSpriteAtlas)),
            "/home/neon/Desktop/SimpleServer/DOEngine/assets/tocaboca_spite_test.jpg"
        );
      
        for(int i= 0; i < 100; i++)
        {
            
            auto dGameObject =  new doengine::DraggableGameObject(
                rand()%600+1,
                rand()%500+1,
                1,
                1
            );
            dGameObject->setSpriteOffset(spriteOffsets);
            gamesamples.push_back(dGameObject);
        }
         

        bg = new doengine::Texture("/home/neon/Desktop/SimpleServer/DOEngine/assets/homebg1.jpg");
        stuff1 = new doengine::Texture("/home/neon/Desktop/SimpleServer/DOEngine/assets/tocaboca_spite_test.jpg");
        
        selected = new doengine::SelectionRect();
        selected->setFont(fontsrc);
 
    }

    virtual void MouseMove(const Mouse& mouse){
        for(auto it : gamesamples){
           it->updateCoords(mouse.getMousePosition());
       }
    }

    virtual void MouseButtonDown(const Mouse& mouse){
         for(auto it : gamesamples){
           it->setSelectedIfCollided(mouse.getMousePosition());
       }
    }

    virtual void MouseButtonUp(const Mouse& mouse){
     for(auto it : gamesamples){
           it->setSelected(false);
       }
    }

   virtual void OnKeydown(const Keyboard& keyboard)
   {
        
       auto key = keyboard.getKeysBitset();
       
       if(key[SDL_SCANCODE_ESCAPE])
       {
          doengine::Application::getApplication()->Quit();
       }

       if(key[SDL_SCANCODE_Q])
       {

       }

       if(key[SDL_SCANCODE_W])
       {

       }

       if(key[SDL_SCANCODE_DOWN])
       {
      
       }
       if(key[SDL_SCANCODE_RIGHT])
       {  

       }

        if(key[SDL_SCANCODE_UP])
       {
             
       }
       if(key[SDL_SCANCODE_LEFT])
       {

       }

   }

   virtual void OnKeyup(const Keyboard&){}

    virtual void OnExit(){}
    
    virtual void Update(float elapsed)
    {
        ///panel.Update();
    }

    virtual void Render()
    {
       doengine::Rect bgRect{
          10,
          200,
          doengine::Application::getApplication()->getW(),
          doengine::Application::getApplication()->getH()/2
       };

       renderer->DrawFillRect({0,0,100,100}, doengine::Colors::blue5);
       //// bg->Draw(bgRect);
        stuff1->Draw({0,0,499,347});
       
       for(auto it : gamesamples){
         it->render(renderer);
       }
       selected->render(renderer);
    }
 
   
};


int main(int argc, char *argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{1200, 980};
    app->createWindow(rect);
    auto playstate = new PlayState();
    app->addState( playstate,  playing);
    app->setState(playing );
 
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