#pragma once
#include "FPSManager.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "WindowManager.h"
#include <memory.h>
///#include "DOEngine.h"

namespace doengine
{
class GameState;
class FpsManager;
class GameStateManager;
class WindowManager;
class Renderer;

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
    long getElapsedTime();
    uint32_t getDeltaTime();
    void setW(int w);
    void setH(int h);
    void setSize(int w, int h);
    int getH();
    int getW();
    Rect getDisplayMode(int m=0);
    void SetWindowPencilColor(const Color& color);
    void clearScreen(const Color& color);
    void addState(GameState* state, int id);
    void setState(int id);
  private:
    void destroy();
};

} // namespace doengine