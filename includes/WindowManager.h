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
    virtual std::shared_ptr<doengine::Renderer>  getRenderer() = 0;
    virtual bool isValid() = 0;
    virtual void clearScreen(const Color& color) = 0;
    virtual void setPincelColor(const Color& color) = 0;
    virtual void updateScreen() = 0;
    virtual void setFullScreen() = 0;
    virtual void setWindowMode() = 0;
    virtual void setSize(const Rect& rect) = 0;
    virtual void* getNativeWindowFormatBuffer() = 0;
    virtual Rect getWindowDisplayMode(int m) = 0;
    static std::shared_ptr<WindowManager> getWindowManager();

  protected:
    std::shared_ptr<doengine::Renderer>  render;
    
    bool run;
    Rect window_rect;
    Rect screen_rect;
    bool support_opengl = false;
};

} // namespace doengine