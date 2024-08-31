#pragma once
#include "Renderer.h"
#include "SDLRenderer.h"
#include "WindowManager.h"
#include <SDL2/SDL.h>

namespace doengine
{

/// @brief this class is for internal use only it will instance by Application
class SDLWindowManager : public WindowManager
{

    SDLRenderer* render;

    SDL_Window* window;

    bool run;

    SDL_Rect window_rect;

    SDL_DisplayMode mode;

  public:
    SDLWindowManager() : WindowManager()
    {
    }
    virtual ~SDLWindowManager()
    {
    }
    virtual bool createWindow(const Rect& rect) override;
    virtual bool createWindow() override;
    virtual Renderer* getRenderer() override;
    virtual bool isValid() override;
    virtual void clearScreen(const Color& color) override;
    virtual void setPincelColor(const Color& color) override;
    virtual void updateScreen() override;
    virtual void setFullScreen() override;
    virtual void setWindowMode() override;
    virtual void setSize(const Rect& rect) override;

    virtual void* getNativeWindowFormatBuffer() override;
};

} // namespace doengine