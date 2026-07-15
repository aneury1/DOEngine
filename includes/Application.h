
/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */
#pragma once

#include <memory.h>


#include "FPSManager.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "WindowManager.h"
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
     
    std::shared_ptr<WindowManager> windowManager;

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

    bool IsRunning() const;

    Renderer* getRender() const;
    std::shared_ptr<WindowManager> getWindow();

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