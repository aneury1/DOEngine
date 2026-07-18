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


#ifndef SDL_OPENGL_WINDOW_MANAGER_H_DEFINED
#define SDL_OPENGL_WINDOW_MANAGER_H_DEFINED
#include "DOEngine_SDL_includes.h"

#include "SDLOpenglRenderer.h"
#include "SDLWindowManager.h"

namespace doengine 
{
    class  SDLOpenglWindowManager : public WindowManager
    {

        private:
        SDL_Window *window;
        void initEngine();
        public:
        virtual bool Quit()override;
        SDLOpenglWindowManager();
        virtual ~SDLOpenglWindowManager();
        virtual bool createWindow(const Rect& rect) override;
        virtual bool createWindow() override;
        virtual std::shared_ptr<Renderer> getRenderer() override;
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
}

#endif /// SDL_OPENGL_WINDOW_MANAGER_H_DEFINED