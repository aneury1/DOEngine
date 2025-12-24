#pragma once

#include <memory>

#include "Geometric.h"
#include "Renderer.h"

namespace doengine
{

class Renderer;

class WindowManager
{
  public:
    WindowManager()
    {
    }
    WindowManager(const WindowManager&) = default;
    virtual ~WindowManager()
    {
    }
    virtual bool createWindow(const Rect& rect) = 0;
    virtual bool createWindow() = 0;
    virtual Renderer* getRenderer() = 0;
    virtual bool isValid() = 0;
    virtual void clearScreen(const Color& color) = 0;
    virtual void setPincelColor(const Color& color) = 0;
    virtual void updateScreen() = 0;
    virtual void setFullScreen() = 0;
    virtual void setWindowMode() = 0;
    virtual void setSize(const Rect& rect) = 0;
    virtual void* getNativeWindowFormatBuffer() = 0;
    virtual Rect getWindowDisplayMode(int m) = 0;
    static WindowManager* getWindowManager();

  protected:
    Renderer* render;
    
    bool run;
    Rect window_rect;
    Rect screen_rect;
    bool support_opengl = false;
};

} // namespace doengine