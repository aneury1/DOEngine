
#include "Application.h"
#include "Grids.h"
#include <Event.h>
#include <GameState.h>
#include "DOEngine_SDL_includes.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace doengine
{

struct TileMap
{
    enum class TileMapMode
    {
        Playing,
        Painting,
        Debuging
    };

    struct TilemapTexturePainter
    {
        Texture* texture;
        Renderer* render;
        Rect offset;
        int tsize;
        

        TilemapTexturePainter(Renderer* render, int tisize)
        {
            offset.x = 20;
            offset.y = 20;
            offset.w = 400;
            offset.h = 600;
            this->render = render;
            texture = new Texture("/home/neon/Documents/projects/"
                                  "other_projects/RTP/ChipSet/Exterior.png");
            offset.w = texture->getWidth() * 2;
            offset.h = texture->getHeight() * 2;
        }

        void RenderScreen()
        {
            render->DrawFillRect(offset, gray);
            texture->Draw(offset);
        }

        bool MouseInside()
        {
            doengine::Point mouse;
            doengine::Event::getMousePosition(&mouse);

            return checkCollisionPointVsRect(offset, mouse);
        }
    };


    bool isRenderingTheEditor(){
        return mode != TileMapMode::Playing;
    }

    TileMapMode mode = TileMapMode::Debuging;

    int rows;
    int cols;
    int tilesize = 32;
    int padding_left = 0;
    int padding_top = 0;

    Renderer* renderer;

    TilemapTexturePainter* mapTexturePainter = nullptr;

    TileMap(int r, int c);
    TileMap(int r, int c, int tilesize);

    void ShowEditControl()
    {
        if (!mapTexturePainter)
            mapTexturePainter = new TilemapTexturePainter(renderer, 16);
        mapTexturePainter->RenderScreen();
    }

    void setTileMapMode(const TileMapMode& mode)
    {
        this->mode = mode;
    }
    void update();
    void render();

    int getTileSize()
    {
        return tilesize;
    }

    void setTileSize(int tsize)
    {
        tilesize = tsize;
    }

    int getPaddingLeft()
    {
        return padding_left;
    }
    int getPaddingTop()
    {
        return padding_top;
    }
    void setPaddingLeft(int p)
    {
        padding_left = p;
    }
    void setPaddingTop(int p)
    {
        padding_top = p;
    }

    struct Tile
    {
        Rect offset;
        Rect original_offset;
        bool filled = false;
        TileMap* tilemap_ref;
        Tile(const Rect& offset, bool f = false)
        {
            original_offset = this->offset = offset;
            filled = f;
        }
        Tile(TileMap* m, const Rect& offset, bool f = false)
        {
            original_offset = this->offset = offset;
            filled = f;
            tilemap_ref = m;
        }
        void Draw(Renderer* render, const Color& color)
        {
            render->DrawRect(offset, color);
            if (filled)
            {
                render->DrawFillRect(offset, yellow);
            }
            if (tilemap_ref && tilemap_ref->mode == TileMapMode::Debuging ||
                tilemap_ref->mode == TileMapMode::Painting)
            {
                render->DrawRect(offset, red);
            }
        }
        void reset_position()
        {
            offset = original_offset;
        }
    };
};

TileMap::TileMap(int r, int c)
{
    rows = r;
    cols = c;
    tilesize = 18;
    renderer = Application::getApplication()->getRender();
}
TileMap::TileMap(int r, int c, int tilesize)
{
    rows = r;
    cols = c;
    this->tilesize = tilesize;
    renderer = Application::getApplication()->getRender();
}

void TileMap::update()
{
}

void TileMap::render()
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            Rect offset =
                Rect{(c * tilesize) + padding_left,
                     (r * tilesize) + padding_top, tilesize, tilesize};
            Point mouse;
            Event::getMousePosition(&mouse);
            bool filled = checkCollisionPointVsRect(offset, mouse);

            Tile(this, offset, filled).Draw(renderer, red);
            // renderer->DrawRect(offset, red);
        }
    }

    ShowEditControl();
}

} // namespace doengine

struct PongState : public doengine::GameState
{
    doengine::Renderer* render;
    doengine::TileMap* map; //(32,32);
    virtual void OnEnter()
    {
        map = new doengine::TileMap(16, 16, 72);
        render = doengine::Application::getApplication()->getRender();
    }
    virtual void OnExit()
    {
    }
    virtual void Update(float elapsed)
    {

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_A))
        {
            map->setTileSize(map->getTileSize() + 1);
        }

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_B))
        {
            map->setTileSize(map->getTileSize() - 1);
        }

        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_S))
        {
            map->setPaddingLeft(map->getPaddingLeft() + 1);
        }
        if (doengine::Event::getLastKeyPressed(SDL_SCANCODE_D))
        {
            map->setPaddingTop(map->getPaddingTop() + 1);
        }
    }
    virtual void Render()
    {

        doengine::Point mouse;
        doengine::Event::getMousePosition(&mouse);
        render->setDrawColor(doengine::green);
        render->clear();
        map->render();
        if(!map->isRenderingTheEditor())
            render->FillCircle(mouse.x, mouse.y, 30, doengine::blue);
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
    doengine::Rect rect{1800, 900};
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
