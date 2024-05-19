#pragma once
#include "FPSManager.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "WindowManager.h"
#include <memory.h>

namespace doengine
{

class FpsManager;
class GameStateManager;
class WindowManager;
class Renderer;

class ClassIdentifier
{
  public:
    virtual std::string getClassIdentifier() = 0;
};

class Application
{
    WindowManager* windowManager;

    Renderer* render;

    GameStateManager* gsm;

    FpsManager* fps_handler;

    Rect window_rect;

    bool run;

    bool dirty;

    static Application* applicationObject;

    Application();

    ~Application();

    void _internalResize();

  public:
    static Application* getApplication()
    {
        if (applicationObject == nullptr)
            applicationObject = new Application();
        return applicationObject;
    }

    const bool IsRunning() const;

    Renderer* getRender() const;
    WindowManager* getWindow();

    void createWindow(const Rect& rect);

    void setFullScreen();
    void setWindowMode();

    void PollEvent();
    void Update();
    void Render();
    void Quit();

    long getElapsedTime()
    {
        return fps_handler->getElapsedTime();
    }

    void setW(int w)
    {
        window_rect.w = w;
        _internalResize();
    }
    void setH(int h)
    {
        window_rect.h = h;
        _internalResize();
    }
    void setSize(int w, int h)
    {
        window_rect.w = w;
        window_rect.h = h;
        _internalResize();
    }
    int getH()
    {
        return window_rect.h;
    }
    int getW()
    {
        return window_rect.w;
    }

    void SetWindowPencilColor(const Color& color);

    void clearScreen(const Color& color);

    void addState(GameState* state, int id)
    {
        gsm->AddState(id, state);
    }

    void setState(int id)
    {
        gsm->SetState(id);
    }

  private:
    void destroy();
};

}; // namespace doengine