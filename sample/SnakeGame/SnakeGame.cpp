/*

AnnetteWorld: Allow Gamers to build Homes
WIP: Create MainScreen State.
TODO: Change Graphics Depends on Seasons and Having Fallback

TODO: Create Login/Entry
TODO: Create Setting State
TODO: Create PArent Setting State.

... More to add

*/

#include "Application.h"
#include "DraggableGameObject.h"
#include "Event.h"
#include "FontCache.h"
#include "GameObject.h"
#include "GameState.h"
#include "Logger.h"
#include "MenuStringList.h"
#include "MessageBox.h"
#include "Mouse.h"
#include "SelectionRect.h"
#include "Sprite.h"
#include "SpriteOffset.h"
#include "TTFText.h"
#include "TextField.h"
#include "Texture.h"
#include "Tile.h"
#include "TileMapEditor.h"
#include "Tilemap.h"
#include "UI.h"
#include "Utils.h"

#include <SDL2/SDL.h>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

using doengine::Application;
using doengine::checkCollision;
using doengine::Color;
using doengine::GameObject;
using doengine::GameState;
using doengine::KeyboardInputhandlingEvent;
using doengine::Point;
using doengine::Rect;
using doengine::Renderer;

enum class Movement
{
    Right,
    Left,
    Up,
    Down
};
constexpr int MAP_COLUMN_COUNT =16;
constexpr int MAP_ROW_COUNT =16;
constexpr int SCALE_FACTOR_PER_SIZE = 32;

Rect getRandomPos()
{
    Rect rect{(rand() % MAP_COLUMN_COUNT + 0) * 32, (rand() % MAP_ROW_COUNT + 0) * 32, 32, 32};
    return rect;
}

struct Snake : public GameObject, public KeyboardInputhandlingEvent
{
    std::vector<Rect> snake; // Just store rectangles
    Rect fruit;
    float currentTimeStamp = 0.0f;
    Movement movement = Movement::Right;
    float accum = 0;
    float speed = 0.6f;
    int score = 0;
    Snake()
    {
        doengine::TextureManager::getTextureManager()->loadTextureFromFile("snake", "/home/neonland/Documents/DOEngine/assets/gfx/sprites/snake1b.png");
        snake.push_back(getRandomPos());
        fruit = getRandomPos();
        score++;
        if((score%3)==0)
        {
            speed--;
        }
    }

    void checkCollisionItSelf()
    {
        auto head = snake[0];
        for(size_t i = 1;i<snake.size();i++)
        {
            if(checkCollision(head, snake[i]))
            {
                snake.clear();
                snake.push_back(getRandomPos());
            }
        }
    }

    void Move()
    {
        // Check collision before moving
        Rect nextHead = snake[0];

        // Calculate next head position
        switch (movement)
        {
        case Movement::Right:
            nextHead.x = (nextHead.x < 15 * 32) ? nextHead.x + 32 : 0;
            break;
        case Movement::Left:
            nextHead.x = (nextHead.x > 0) ? nextHead.x - 32 : 15 * 32;
            break;
        case Movement::Up:
            nextHead.y = (nextHead.y > 0) ? nextHead.y - 32 : 15 * 32;
            break;
        case Movement::Down:
            nextHead.y = (nextHead.y < 15 * 32) ? nextHead.y + 32 : 0;
            break;
        }

        // Check if eating fruit
        if (doengine::checkCollision(nextHead, fruit))
        {
            snake.insert(snake.begin(), nextHead); // Add new head
            fruit = getRandomPos();
            return;
        }

        checkCollisionItSelf();

        // Move body: each segment takes position of the one in front
        for (int i = snake.size() - 1; i > 0; i--)
        {
            snake[i] = snake[i - 1];
        }

        // Move head to next position
        snake[0] = nextHead;
    }

    virtual void Render() override
    {
        renderer->DrawFillRect(fruit, doengine::Colors::green);
        renderer->DrawRect(fruit, doengine::Colors::white, 2);
        for (auto segment : snake)
        {
            segment.w =SCALE_FACTOR_PER_SIZE; 
            segment.h =SCALE_FACTOR_PER_SIZE; 
            renderer->DrawFillRect(segment, doengine::Colors::red);
        }
    }

    virtual void OnKeydown(const Keyboard& keyboard)
    {
        auto keys = keyboard.getKeysBitset();
        Movement newMovement = movement;

        if (keys[doengine::SCANCODE_LEFT])
            newMovement = Movement::Left;
        else if (keys[doengine::SCANCODE_RIGHT])
            newMovement = Movement::Right;
        else if (keys[doengine::SCANCODE_UP])
            newMovement = Movement::Up;
        else if (keys[doengine::SCANCODE_DOWN])
            newMovement = Movement::Down;

        // Prevent 180-degree turns
        if ((newMovement == Movement::Left && movement == Movement::Right) ||
            (newMovement == Movement::Right && movement == Movement::Left) ||
            (newMovement == Movement::Down && movement == Movement::Up) ||
            (newMovement == Movement::Up && movement == Movement::Down))
        {
            return; // Ignore invalid direction change
        }

        movement = newMovement;
    }
    virtual void OnKeyup(const Keyboard&)
    {
    }


    virtual void Update(float elapsed)
    {
        accum += elapsed+0.1f;
        if (accum < speed)
            return;
        Move();
        accum = 0.0f;
    }
};

struct SnakeState : public GameState,
                                public KeyboardInputhandlingEvent
{

    
    Snake snake;
    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float elapsed);
    virtual void Render();
    virtual void OnKeydown(const Keyboard&);
    virtual void OnKeyup(const Keyboard&);
};

void SnakeState::OnEnter()
{
 
}
void SnakeState::OnExit()
{
}
void SnakeState::Update(float elapsed)
{
    snake.Update(elapsed);
}
void SnakeState::Render()
{

    for (int r = 0; r < 16; r++)
    {
        for (int c = 0; c < 16; c++)
        {
            Rect rect{c * SCALE_FACTOR_PER_SIZE, r * SCALE_FACTOR_PER_SIZE, SCALE_FACTOR_PER_SIZE, SCALE_FACTOR_PER_SIZE};
            snake.getRenderer()->DrawRect(rect, doengine::Colors::white, 1);
        }
    }
  
    snake.Render();
}
void SnakeState::OnKeydown(const Keyboard&)
{
}
void SnakeState::OnKeyup(const Keyboard&)
{
}

int main(int argc, char* argv[])
{

    auto app = doengine::Application::getApplication();

    doengine::Rect rect{1200, 900};
    app->createWindow(rect);
    app->setSize(rect.w, rect.h);

    auto playstate = new SnakeState();
    app->addState(playstate, 1);
    app->setState(1);

    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->clearScreen(doengine::Colors::black1);
        app->Render();
    }
    app->Quit();
    return 0;
}
