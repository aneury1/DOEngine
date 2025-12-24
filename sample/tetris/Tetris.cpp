
#include "Application.h"
#include "GameObject.h"
#include "Grids.h"
#include <Event.h>
#include <GameState.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
using namespace doengine;

constexpr int ROWS = 20;
constexpr int COLUMNS = 10;


struct Block{
  int id;
  Block(){

  }

};


struct TetrisGrid : public GameObject
{

    std::vector<Color> colors;
    int grid[ROWS][COLUMNS];
    int numRows;
    int numCols;
    int cellsize;
    Renderer* renderer;

    std::vector<Color> getColors()
    {
        return {doengine::Colors::gray, doengine::Colors::green, doengine::Colors::red, 
        doengine::Colors::orange, doengine::Colors::yellow, doengine::Colors::purple, doengine::Colors::cyan, doengine::Colors::blue};
    }

    void reset()
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLUMNS; c++)
            {
                grid[r][c] = 0;
            }
        }
    }

    TetrisGrid(Renderer *r)
    {
        renderer = r;
        numRows = ROWS;
        numCols = COLUMNS;
        cellsize = 32;
        colors = getColors();
        reset();
    }
    virtual void Update(float timer = 0) override
    {
    }

    virtual void Render() override
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLUMNS; c++)
            {
                int value = grid[r][c];
                Rect rect{c*cellsize+1, r*cellsize+1, cellsize-1, cellsize-1};
                renderer->DrawRect(rect, colors[value]);
            }
        }
    }
};

struct TetrisState : public doengine::GameState
{
    doengine::Renderer* render;
    TetrisGrid* tetris= nullptr;
    virtual void OnEnter()
    {
        render = Application::getApplication()->getRender();
        tetris = new TetrisGrid(render);
    }
    virtual void OnExit()
    {
    }
    virtual void Update(float elapsed)
    {


        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_A))
        {
        }

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_B))
        {
        }

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_S))
        {
        }
        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_D))
        {
        }
        tetris->Update();
    }
    virtual void Render()
    {
        render->setDrawColor(doengine::Colors::black);
        render->clear();
        tetris->Render();
    }
};

enum SampleStateId : int
{
    TetrisStateID = 1
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{800, 900};
    app->createWindow(rect);
    auto game = new TetrisState();
    app->addState(game, TetrisStateID);
    app->setState(TetrisStateID);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}
