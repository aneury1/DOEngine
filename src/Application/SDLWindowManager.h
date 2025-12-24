#pragma once
#include "DOEngine_SDL_includes.h"
#include "Renderer.h"
#include "SDLRenderer.h"
#include "WindowManager.h"

namespace doengine
{

/// @brief this class is for internal use only it will instance by Application
class SDLWindowManager : public WindowManager
{
  protected:
    SDL_DisplayMode mode;
    SDL_Window* window;

  public:
    SDLWindowManager();
    virtual ~SDLWindowManager();
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
    virtual Rect getWindowDisplayMode(int m);
    virtual void* getNativeWindowFormatBuffer() override;
};

} // namespace doengine