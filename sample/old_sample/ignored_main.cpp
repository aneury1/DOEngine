#include "DOEngine_SDL_includes.h"
#include "Application.h"
#include <GameState.h>
#include <Event.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace doengine{

 


struct TileMap
{
    int rows;
    int cols;
    int tilesize =32;
    int padding_left = 0;
    int padding_top  = 0;
    Renderer* renderer;
    TileMap(int r, int c);
    TileMap(int r, int c, int tilesize);
   
    void update();
    void render();

    int getTileSize(){
        return tilesize;
    }
   
    void setTileSize(int tsize ){
        tilesize= tsize;
    }
 
    int getPaddingLeft(){return padding_left;}
    int getPaddingTop(){return padding_top;}
    void setPaddingLeft(int p){padding_left = p;}
    void setPaddingTop(int p){padding_top = p;}

    struct Tile{
       Rect offset;
       bool filled =false;
       Tile(const Rect& offset,bool f=false)
       {
        this->offset = offset;
        filled = f;
       }
       void Draw(Renderer *render,const Color& color){
           render->DrawRect(offset, color);
           if(filled){
              render->DrawFillRect(offset, yellow);
           }
       }
    };
};

TileMap::TileMap(int r, int c)
{
    rows= r;
    cols= c;
    tilesize=18;
    renderer = Application::getApplication()->getRender();
}
TileMap::TileMap(int r, int c, int tilesize)
{
    rows= r;
    cols= c;
    this->tilesize =tilesize;
    renderer = Application::getApplication()->getRender();
}


void TileMap::update()
{

}

void TileMap::render()
{
    for(int r=0; r<rows;r++)
    {
        for(int c=0;c<cols;c++)
        {
            Rect offset=Rect{(c*tilesize)+padding_left,(r*tilesize)+padding_top,tilesize,tilesize};
            Point mouse;
            Event::getMousePosition(&mouse);
            bool filled = checkCollisionPointVsRect(offset,mouse);
           
            Tile(offset, filled).Draw(renderer, red);
            //renderer->DrawRect(offset, red);
        }
    }
}



}











struct PongState : public doengine::GameState
{
    doengine::Renderer *render;
    doengine::TileMap* map;//(32,32);
    virtual void OnEnter()
    {
        map = new doengine::TileMap(16,16,72);
        render = doengine::Application::getApplication()->getRender();
    }
    virtual void OnExit()
    {
    }
    virtual void Update(float elapsed)
    {
             
         if(doengine::Event::getLastKeyPressed(SDL_SCANCODE_A)){
            map->setTileSize(map->getTileSize()+1);
         }

         if(doengine::Event::getLastKeyPressed(SDL_SCANCODE_B)){
            map->setTileSize(map->getTileSize()-1);
         }

         if(doengine::Event::getLastKeyPressed(SDL_SCANCODE_S)){
            map->setPaddingLeft(map->getPaddingLeft()+1);
         }
         if(doengine::Event::getLastKeyPressed(SDL_SCANCODE_D)){
            map->setPaddingTop(map->getPaddingTop()+1);
         }
    }
    virtual void Render()
    {
        
        doengine::Point mouse;
        doengine::Event::getMousePosition(&mouse);
        render->setDrawColor(doengine::green);
        render->clear();
        map->render();
        render->FillCircle(mouse.x,mouse.y, 30, doengine::blue);
        render->DrawPoint(mouse, doengine::red);
        
    }
};


enum SampleStateId : int
{
    pongStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{1800,900};
    app->createWindow(rect);
    auto pongState = new PongState();
    app->addState(pongState, pongStateID);
    app->setState(pongStateID);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}


