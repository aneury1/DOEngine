#include "Application.h"
#include "Event.h"
#include "EventHandler.h"
#include "GameState.h"
#include "Geometric.h"
#include "Keyboard.h"
#include "MusicHandler.h"
#include "SDLMusicHandler.h"

using doengine::Color;
using doengine::Rect;
using doengine::Application;
using doengine::GameState;
using doengine::Renderer;



template<typename T, const int R, int C>
struct DataMatrix
{


};



enum class BlockType : int
{
   None = 0,
   Wall = 1,
   Brick = 2,
   Watter = 3,
   Glass = 4,
   Grass = 5
};

struct Tile
{
    Renderer renderer;
    BlockType block;
    Rect rect;
    unsigned int life;
    Tile(Renderer *renderer, const Rect& rect):
        renderer{renderer},
        rect{rect}
    {

    }
    void Draw()
    {
        if(block == BlockType::None) return;

        switch (block)
        {
            case BlockType::Wall:
            case BlockType::Brick:
            case BlockType::Grass:
            case BlockType::Watter:

        }
    }
};



struct RawBattlePlayState : public GameState
{

    Rect rect{0,0,100,100};
    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float elapsed);
    virtual void Render();
};

void RawBattlePlayState::OnEnter(){}
void RawBattlePlayState::OnExit(){}
void RawBattlePlayState::Update(float elapsed){}
void RawBattlePlayState::Render()
{
  auto rendere = Application::getApplication()->getRender();
  rendere->DrawRect(rect, Color{0xFF, 0xfF, 0, 0xFF});
}




enum RawBattleState : int
{
    StateId = 1
};


int main(int argc, char **argv)
{
    auto app = Application::getApplication();
    app->createWindow(Rect{1200, 900});
    auto pongState = new RawBattlePlayState();
    app->addState(pongState, StateId);
    app->setState(StateId);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;

    return 0;
}