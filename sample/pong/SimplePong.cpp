
#include "Application.h"
#include "GameObject.h"
#include "Grids.h"
#include "TTFText.h"
#include <Event.h>
#include <GameState.h>
#include "DOEngine_SDL_includes.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace doengine;

struct Paddle : public GameObject
{

    enum class PaddleWhere
    {
        Left,
        Right,
        Top,
        Bottom
    };

    enum class PaddleMovement
    {
        Up,
        Down
    };

    Renderer* renderer;
    Rect position;
    double spy = 0;
    PaddleWhere where;

    void reset()
    {
        if (where == PaddleWhere::Left)
        {
            position.x = 72;
            position.y = Application::getApplication()->getH() / 2 - 60;
            position.w = 25;
            position.h = 120;
        }
        else if (where == PaddleWhere::Right)
        {
            position.x = Application::getApplication()->getW() - 30;
            position.y = Application::getApplication()->getH() / 2 - 60;
            position.w = 25;
            position.h = 120;
        }
    }

    void movePaddle(PaddleMovement movement)
    {
        spy = 0;
        switch (movement)
        {
        case PaddleMovement::Up:
            spy -= 12;
            break;
        case PaddleMovement::Down:
            spy = 12;
            break;
        default:
            throw std::runtime_error("This would never happen.");
            break;
        }
    }

    Paddle(const PaddleWhere& where, Renderer* renderer)
    {
        this->renderer = renderer;
        this->where = where;
        reset();
    }

    virtual void Update(float timer = 0)
    {
        position.y += (int)spy;
        spy = 0;
        if(position.y <= 0)
           position.y = 0;
        else if(position.y + position.h> Application::getApplication()->getH()){
           position.y = Application::getApplication()->getH() - position.h;    
        }

    }
    virtual void Render()
    {
        renderer->DrawFillRect(position, doengine::Colors::white);
    }
};

struct Ball : public GameObject
{
    Point point;
    Point speed;
    double radius;
    Renderer* renderer;


    void reset()
    {
        point.x = Application::getApplication()->getW() / 2;
        point.y = Application::getApplication()->getH() / 2;
        radius = 20;
        speed.x = 7;
        speed.y = 7;
    }

    Ball(Renderer* render)
    {
        renderer = render;
        reset();
    }

    virtual void Update(float timer = 0)
    {
        point.x += speed.x;
        point.y += speed.y;

        int w = Application::getApplication()->getW();
        int h = Application::getApplication()->getH();
        if( point.y + radius >= h || point.y - radius <= 0)
        {
           speed.y *= -1;            
        }
        if( point.x + radius >= w || point.x - radius <= 0)
        {
           speed.x *= -1;            
        }
    }
    virtual void Render()
    {
        renderer->FillCircle(point.x, point.y, radius, doengine::Colors::white);
    }
};

struct PongState : public GameState, public KeyDownEvent
{
    Ball* ball;
    Paddle* left;
    Paddle* right;
    Renderer* renderer;
    TTFText *textHandler;

    int leftScore = 0;
    int rightScore= 0;



    virtual void OnEnter()
    {
        textHandler = new TTFText();
        textHandler->setFont("/home/neon/Documents/projects/myprojects/DOEngine/assets/fonts/NirmalaB.ttf", 18);
        textHandler->setColor(doengine::Colors::white);
        Event::AddKeyPressEventListener(this);
        renderer = Application::getApplication()->getRender();
        ball = new Ball(renderer);
        left = new Paddle(Paddle::PaddleWhere::Left, renderer);
        right = new Paddle(Paddle::PaddleWhere::Right, renderer);
    }
    virtual void OnExit()
    {
    }
    virtual void Update(float elapsed)
    {
        ball->Update();
        left->Update();
        right->Update();

        if(checkCollisionCircleRec(ball->point, ball->radius, left->position))
        {
            ball->speed.x *= -1;
        }
        if(checkCollisionCircleRec(ball->point, ball->radius, right->position))
        {
            ball->speed.x *= -1;
        }

        if(ball->point.x <= 0 ||
            ball->point.x >= Application::getApplication()->getW()){

            ball->reset();
        }
        
        
        rightScore = ((ball->point.x) <= ball->radius) ? (rightScore+1):rightScore;
        leftScore = (ball->point.x >= Application::getApplication()->getW()-ball->radius) ? (leftScore+1):leftScore;
        SDL_Log("score %ld <> %ld ==> BALL:[%ld, %ld]", leftScore, rightScore, ball->point.x, ball->point.y);
    
    }

    virtual void Render()
    {
        renderer->setDrawColor(doengine::Colors::black);
        renderer->clear();
        textHandler->DrawText(std::to_string(leftScore).c_str(), 100, 0);
        textHandler->DrawText(std::to_string(rightScore).c_str(),Application::getApplication()->getW() / 2 + 40 , 0);
        renderer->DrawLine(Point{Application::getApplication()->getW() / 2, 0},
                           Point{Application::getApplication()->getW() / 2,
                                 Application::getApplication()->getH()},
                           doengine::Colors::white);
        ball->Render();
        left->Render();
        right->Render();
    }
    void OnKeydown(const Keyboard& key)
    {

        if (SDL_SCANCODE_W == key.getLastKeyPressed())
        {
            left->movePaddle(Paddle::PaddleMovement::Up);
        }

        if (SDL_SCANCODE_S == key.getLastKeyPressed())
        {
            left->movePaddle(Paddle::PaddleMovement::Down);
        }

        if (SDL_SCANCODE_UP == key.getLastKeyPressed())
        {
            right->movePaddle(Paddle::PaddleMovement::Up);
        }

        if (SDL_SCANCODE_DOWN == key.getLastKeyPressed())
        {
            right->movePaddle(Paddle::PaddleMovement::Down);
        }
    }
};

int main(int argc, char* argv[])
{
    auto app = doengine::Application::getApplication();
    doengine::Rect rect{1200, 900};
    app->createWindow(rect);
    auto pongState = new PongState();
    app->addState(pongState, 1);
    app->setState(1);

    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->Render();
    }
    app->Quit();
    return 0;
}