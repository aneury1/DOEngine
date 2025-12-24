#include "DOEngine_SDL_includes.h"
#include "Application.h"
#include <GameState.h>
#include <Event.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Global variable to store the start time
Uint32 startTime = 0;

float GetElapsedTime()
{
    Uint32 currentTime = SDL_GetTicks(); // Get current time in milliseconds
    return (currentTime - startTime) / 10000.0f; // Convert to seconds
}

enum class AlienType{
    Type1,
    Type2,
    Type3
};

struct Alien {
   doengine::Renderer *renderer;
   doengine::Rect offset;
   doengine::Texture *texture;
   AlienType type;

   
   Alien(AlienType type, doengine::Rect offset){
      this->type = type;
      this->offset = offset;
      renderer = doengine::Application::getApplication()->getRender();
   }

   void Draw(){
     switch(type){
        case AlienType::Type1:
            renderer->DrawFillRect(offset, doengine::Colors::yellow1);break;
        case AlienType::Type2:
            renderer->DrawFillRect(offset, doengine::Colors::red);break;
        case AlienType::Type3:
            renderer->DrawFillRect(offset, doengine::Colors::blue5);break;
     }
   }

   void Update(){
 
   }
};





struct Block{
   
   doengine::Rect offset;
   
   void Draw(){
     doengine::Renderer *render = doengine::Application::getApplication()->getRender();
     render->DrawFillRect(offset, doengine::Colors::yellow);
   }

   Block(doengine::Rect o){
    this->offset = o;
    offset.w =3;
    offset.h =3;
   }
};

struct Obstacle{
   doengine::Rect offset;
   
   std::vector<Block> blocks;

   Obstacle(doengine::Rect o){
     offset = o;
     initGrid();
   }
   
   void initGrid(){
     for(int row =0;row < grid.size(); row++)
     {
         for(int col =0; col< grid[0].size(); col++)
         {
            if(grid[row][col]==1){
                int posx = offset.x + (col * 3);
                int posy = offset.y + (row * 3);
                Block block(doengine::Rect{posx, posy, 3,3});
                blocks.emplace_back(block); 
            }
         }
     }
   }


   void Draw(){
    for(auto it : blocks){
        it.Draw();
    }
   }

static std::vector<std::vector<int>>  grid;
};

std::vector<std::vector<int>> Obstacle::grid = {
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
    };










struct Laser
{
    doengine::Renderer* renderer;
    doengine::Rect offset;
    int speed;
    bool active;

    Laser(doengine::Renderer* render, doengine::Rect o, int s)
    {
        speed = s;
        offset = o;
        renderer = render;
        active=true;
    }

    void Update()
    {
        offset.y -= speed;
      
        if(offset.y <= 0){
            active = false;
        }
   
    }

    void setActive(bool v){
        active = v;
    }

    void draw()
    {
        if (renderer && active)
            renderer->DrawRect(offset, doengine::Colors::yellow);
    }
};

struct Spacership
{
    doengine::Renderer* renderer;
    doengine::Texture* texture;
    doengine::Rect offset;
    std::vector<Laser*> firebeam;
    double lastFireTime = 0;
    Spacership(doengine::Renderer* r);
    void Draw();
    void Update();
    void MoveLeft();
    void MoveRight();
    void FireLaser();
};

Spacership::Spacership(doengine::Renderer* r)
{
    texture = nullptr;
    renderer = r;
    offset.x = doengine::Application::getApplication()->getW() / 2;
    offset.y = doengine::Application::getApplication()->getH() - 64;
    offset.w = 32;
    offset.h = 32;
}

void Spacership::Draw()
{
    if (texture)
    {
    }
    else
    {
        renderer->DrawFillRect(offset, doengine::Colors::red);
    }

    for (auto beam : firebeam)
        beam->draw();
}
void Spacership::MoveLeft()
{
    offset.x -= 32;
    if (offset.x < 0)
        offset.x = 0;
}
void Spacership::MoveRight()
{
    offset.x += 32;
    if (offset.x > doengine::Application::getApplication()->getW())
    {
        offset.x = doengine::Application::getApplication()->getW() - 32;
    }
}
void Spacership::FireLaser()
{

    if ((SDL_GetTicks() - lastFireTime) >= 450 || lastFireTime == 0)
    { // 0.35s = 350ms
        doengine::Rect loffset = offset;
        loffset.y -= 32;
        loffset.w = 6;
        loffset.x += 10;
        firebeam.emplace_back(new Laser(renderer, loffset, 1));

        lastFireTime = SDL_GetTicks(); // Store in milliseconds
    }
}

void Spacership::Update()
{
   for(auto beam : firebeam){
      beam->Update();
   }
}

struct SpacerInvaderState : public doengine::GameState
{
    doengine::Renderer* render;
    Spacership* ship;
    
    

    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;

    
    void initAliens(){
        for(int row =0;row < 5;row++){
            for(int col =0;col < 11;col++)
            {   
                static const int cellsize = 32;
                int x =75 + col * cellsize;
                int y =110 + row *cellsize;
                aliens.push_back(Alien(AlienType::Type1, doengine::Rect{x,y,cellsize,cellsize}));
            }
        }
    }
   
    void updateAliens(){
        float speed= 1;
        int w = doengine::Application::getApplication()->getW();
        for(auto& it : aliens){
            int xf = it.offset.x + (it.offset.w);
            int yf = it.offset.y;
            
            if(xf >= w)
            {
               speed *= -speed;
               it.offset.y +=1;
            }

            it.offset.x = xf * speed;
        
        }
    }

    void initObstacles(){
  
       int wobstacle = Obstacle::grid[0].size() * 3;
       int wscreen = doengine::Application::getApplication()->getW();
       int cnt = 4;
       float gap = (wscreen - (wobstacle * cnt)) / 5;
       for(int i=0;i<cnt;i++){
          float offset_x = (i + 1) * gap + i * wobstacle;
          obstacles.push_back(Obstacle{doengine::Rect{offset_x, 400,0,0}});
       }
       bool practice_mode = false;
       if(practice_mode){
            for(int i=0;i<cnt;i++){
            float offset_x = (i + 1) * gap + i * wobstacle;
            obstacles.push_back(Obstacle{doengine::Rect{offset_x, 200,0,0}});
        }
       }
    }

    void DrawObstacle(){
    
       for(auto it : obstacles){
         it.Draw();
       }
    }

    void DrawAliens(){
    
       for(auto it : aliens){
         it.Draw();
       }
    }

    virtual void OnEnter()
    {
        render = doengine::Application::getApplication()->getRender();
        ship = new Spacership(render);
        initObstacles();
        initAliens();
    }
    virtual void OnExit()
    {
    }
    virtual void Update(float elapsed)
    {

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_A))
        {
        }

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_SPACE))
        {
            ship->FireLaser();
        }

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_LEFT))
        {
            ship->MoveLeft();
        }
        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_RIGHT))
        {
            ship->MoveRight();
        }
        ship->Update();
        updateAliens();
    }
    virtual void Render()
    {
        render->setDrawColor(doengine::Color{0x22, 0x22, 0x32, 0x12});
        render->clear();
        DrawObstacle();
        DrawAliens();
        ship->Draw();
    }
};

enum SampleStateId : int
{
    SpaceInvader = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{800, 600};
    app->createWindow(rect);
    auto pongState = new SpacerInvaderState();
    app->addState(pongState, SpaceInvader);
    app->setState(SpaceInvader);
    startTime = SDL_GetTicks();
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
        
    }
    app->Quit();
    return 0;
}
