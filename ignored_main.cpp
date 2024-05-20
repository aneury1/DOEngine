#include "Application.h"
#include "Event.h"
#include "GameState.h"
#include "Logger.h"
#include "StringUtils.h"
#include "TTFText.h"
#include "Texture.h"
#include "Tilemap.h"

#include <SDL2/SDL.h>
#include <ctime>
#include <iostream>
#include <random>

#include <chrono>
#include <thread>
using namespace std;

#include <arpa/inet.h> // For inet_pton
#include <cstring>     // For memset
#include <iostream>
#include <netinet/in.h> // For sockaddr_in
#include <stdlib.h>
#include <sys/socket.h> // For socket functions
#include <time.h>
#include <unistd.h> // For close
using namespace doengine;

int ballSpeed = 10;

enum class PaddleHandler : uint8_t
{
    Right,
    Left,
    Top,
    Bottom,
    Center
};

struct GameBall : public GameObject
{

    Application* app;

    Rect rect;
    Point speed;

    int radio;

    void initBallPosition()
    {
        rect.x = 400;
        rect.y = 400;
        rect.w = 30;
        rect.h = 30;
        radio = 10;
        speed.x = (rand() % 2 + 0) == 0 ? 1 : -1;
        speed.y = (rand() % 2 + 0) == 0 ? 1 : -1;
    }

    GameBall()
    {
        app = Application::getApplication();
        initBallPosition();
    }

    virtual void Update(float timer = 0)
    {
        rect.x = rect.x + (ballSpeed * speed.x);
        rect.y = rect.y + (ballSpeed * speed.y);

        if (rect.x <= 0 || rect.x >= app->getW() - rect.w)
            speed.x = -speed.x;
        if (rect.y <= 0 || rect.y >= app->getH() - rect.h)
            speed.y = -speed.y;
    }
    virtual void Render()
    {
        app->getRender()->DrawFillRect(rect, red);
        app->getRender()->FillCircle(rect.x, rect.y, radio, green);
    }
};

struct Paddle : public GameObject
{
    PaddleHandler handler;

    Rect paddlePosition;

    Point speed;

    Color color;

    int score;

    void initPaddlePosition()
    {
        auto app = Application::getApplication();
        speed.x = 0;
        speed.y = 0;
        switch (handler)
        {
        case PaddleHandler::Left:
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;
            paddlePosition.x = 30;
            paddlePosition.y = (app->getH() / 2) - 100;
            paddlePosition.w = 32;
            paddlePosition.h = 200;
            break;
        case PaddleHandler::Right:
            paddlePosition.x = app->getW() - 60;
            paddlePosition.y = (app->getH() / 2) - 100;
            paddlePosition.w = 32;
            paddlePosition.h = 200;
            color.r = 255;
            color.g = 0;
            color.b = 5;
            color.a = 255;
            break;
        default:
            break;
        }
    }

    Paddle(const PaddleHandler& handler) : handler{handler}
    {
        initPaddlePosition();
    }
    enum class MovementDirection
    {
        Up,
        Down,
        Left,
        Right,
        None
    };
    void Move(MovementDirection mov)
    {
        speed.y = 0;
        speed.x = 0;
        SDL_Log("Pads movement %d %d", paddlePosition.y, paddlePosition.x);
        switch (mov)
        {
        case MovementDirection::None:
            speed.y = 0;
            break;
        case MovementDirection::Up:
            speed.y = -1;
            break;
        case MovementDirection::Down:
            speed.y = 1;
            break;
        default:
            break;
        }
    }

    virtual void Update(float timer = 0)
    {
        paddlePosition.y += (10 * speed.y);
        paddlePosition.x += (10 * speed.x);

        SDL_Log("Pads %d %d", paddlePosition.y, paddlePosition.x);
    }
    virtual void Render()
    {
        SDL_Log("Pads render %d %d", paddlePosition.y, paddlePosition.x);
        auto app = Application::getApplication();
        app->getRender()->DrawFillRect(paddlePosition, color);
    }
};

class PongGameState : public GameState, KeyDownEvent
{

    int numberOfPlayer;

    std::vector<Paddle> pads;
    GameBall ball;

    virtual void OnKeydown(int code)
    {

        if (code == 119)
        {
            std::cout << "Code up << " << code << "\n";
            for (auto& pad : pads)
            {
                pad.Move(Paddle::MovementDirection::Up);
            }
        }
        else if (code == 115)
        {
            std::cout << "Code down << " << code << "\n";
            for (auto& pad : pads)
            {
                pad.Move(Paddle::MovementDirection::Down);
            }
        }
    }

    virtual void OnEnter()
    {
        Event::AddKeyPressEventListener(this);
        pads.emplace_back(Paddle{PaddleHandler::Left});
        pads.emplace_back(Paddle{PaddleHandler::Right});
        // pads.emplace_back(Paddle{PaddleHandler::Right});
        // pads.emplace_back(Paddle{PaddleHandler::Top});
    }
    virtual void OnExit()
    {
    }
    virtual void Update(float elapsed)
    {
        for (auto it : pads)
            it.Update();
        ball.Update();
    }
    virtual void Render()
    {
        for (auto it : pads)
            it.Render();
        ball.Render();
    }
};

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    auto app = Application::getApplication();
    app->createWindow({1000, 800});
    auto testState = new PongGameState();

    app->addState(testState, 1);
    app->setState(1);

    unsigned char c = 20;
    Color color(c);
    while (app->IsRunning())
    {
        app->PollEvent();
        app->Update();
        app->clearScreen(color);
        app->Render();
    }

    return 0;
}