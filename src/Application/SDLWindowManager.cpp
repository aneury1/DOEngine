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


#include "SDLWindowManager.h"
#include "Logger.h"

namespace doengine
{
bool SDLWindowManager::createWindow()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    int img_flags =     IMG_INIT_JPG | IMG_INIT_PNG     | IMG_INIT_TIF     | IMG_INIT_WEBP   |  IMG_INIT_JXL  | IMG_INIT_AVIF;
    
    IMG_Init(img_flags);
    
    SDL_DisplayMode mode;

    SDL_GetCurrentDisplayMode(0, &mode);
    SDL_Log("created render"); 

    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, mode.w, mode.h,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    SDL_Log("created render"); 

    render = std::make_shared<SDLRenderer>(SDL_CreateRenderer(
        window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));

    SDL_Log("created render"); 
    run = render->isRenderOk();

    window_rect.w = mode.w;

    window_rect.h = mode.h;

    return run;
}

SDLWindowManager::~SDLWindowManager()
{

}

SDLWindowManager::SDLWindowManager() : WindowManager()
{
    support_opengl = false;
    LogOuput(logger_type::Information, "Simple SDL Window Not Opengl Support");
    SDL_Init(SDL_INIT_EVERYTHING);
        int img_flags =     IMG_INIT_JPG | IMG_INIT_PNG     | IMG_INIT_TIF     | IMG_INIT_WEBP   |  IMG_INIT_JXL  | IMG_INIT_AVIF;
    IMG_Init(img_flags);
    LogOuput(logger_type::Information, "Simple SDL Window Created");
}

bool SDLWindowManager::createWindow(const Rect& rect)
{

LogOuput(logger_type::Information, "Simple SDL Window Created Rect %d %d %d %d", rect.w, rect.h, rect.x, rect.y);
    SDL_GetCurrentDisplayMode(0, &mode);

    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, rect.w, rect.h,
                              SDL_WINDOW_SHOWN /*| SDL_WINDOW_BORDERLESS*/);

    render = std::make_shared<SDLRenderer>(SDL_CreateRenderer(
        window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));

    TTF_Init();
 
    run = render->isRenderOk();

    window_rect.w = rect.w;

    window_rect.h = rect.h;

    return run;
}

bool SDLWindowManager::isValid()
{
    return run;
}

void SDLWindowManager::setPincelColor(const Color& color)
{
    SDL_SetRenderDrawColor((SDL_Renderer*)render->getNativeRenderer(), color.r,
                           color.g, color.b, 255);
}

void SDLWindowManager::clearScreen(const Color& color)
{
    SDL_SetRenderDrawColor((SDL_Renderer*)render->getNativeRenderer(), color.r,
                           color.g, color.b, 255);
    SDL_RenderClear((SDL_Renderer*)render->getNativeRenderer());
}

void SDLWindowManager::updateScreen()
{
    SDL_RenderPresent((SDL_Renderer*)render->getNativeRenderer());
}
std::shared_ptr<Renderer> SDLWindowManager::getRenderer()
{
    return render;
}

void SDLWindowManager::setFullScreen()
{
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void SDLWindowManager::setWindowMode()
{
    SDL_SetWindowFullscreen(window, 0);
}
void SDLWindowManager::setSize(const Rect& rect)
{
    SDL_SetWindowSize(window, rect.w, rect.h);
    window_rect.w = rect.w;
    window_rect.h = rect.h;
}

void* SDLWindowManager::getNativeWindowFormatBuffer()
{
    return (void*)window;
}

Rect SDLWindowManager::getWindowDisplayMode(int  )
{
   /*int w, h;
   ///// SDL_GetDesktopDisplayMode(m, &(SDL_DisplayMode){});

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(m, &dm) == 0)
    {
        w = dm.w;
        h = dm.h;
    }
    return Rect{
        0,0,w,h
    };*/ 

    SDL_Rect usable;
    SDL_GetDisplayUsableBounds(0, &usable);

    int usableW = usable.w;
    int usableH = usable.h;
         return Rect{
        0,0,usableW,usableH-100
    };
}


} // namespace doengine