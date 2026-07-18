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


#include "Logger.h"
#include "SDLOpenglWindowManager.h"
#include "SDLOpenglRenderer.h"
#include "DOEngine_SDL_includes.h"

namespace doengine
{
 
SDLOpenglWindowManager::SDLOpenglWindowManager()
{
    
}

bool SDLOpenglWindowManager::Quit(){

    if(render)
        render.reset();
    if(window)
      SDL_DestroyWindow(window);
    SDL_Quit();
    run = false;
    return true;
}

void SDLOpenglWindowManager::initEngine()
{
    window = nullptr;
    render = nullptr;
    
    window_rect.w = 500;
    window_rect.h = 500;

    SDL_Init(SDL_INIT_EVERYTHING);
   
    int img_flags =     IMG_INIT_JPG | IMG_INIT_PNG     | IMG_INIT_TIF     | IMG_INIT_WEBP   |  IMG_INIT_JXL  | IMG_INIT_AVIF;
   
    IMG_Init(img_flags);

    TTF_Init();

    
    LogOuput(logger_type::Information, "SDL Created Window %s", SDL_GetError());
    // Set OpenGL version (4.5 Core)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);



    window = SDL_CreateWindow("  ", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, window_rect.w, window_rect.h,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS |SDL_WINDOW_OPENGL);

    this->support_opengl = true;
       
    this->render = std::make_shared<SDLOpenglRenderer>(window);

    LogOuput(logger_type::Information, "SDL Created Window %s", SDL_GetError());


    setSize(window_rect);
    
    // Enable blending for alpha transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, 500,500);
    
    LogOuput(logger_type::Information, "SDL Created Window %s", SDL_GetError());
    
    run = render->isRenderOk();
    
    LogOuput(logger_type::Information, "SDL Created Window %s", SDL_GetError());
}


SDLOpenglWindowManager::~SDLOpenglWindowManager()
{
}

bool SDLOpenglWindowManager::createWindow(const Rect&  )
{
    initEngine();
    return run;
}

bool SDLOpenglWindowManager::createWindow()
{
    initEngine();
    return run;
}

std::shared_ptr<doengine::Renderer>  SDLOpenglWindowManager::getRenderer()
{
    return render;
}
bool SDLOpenglWindowManager::isValid()
{
    return render!=nullptr;
}

void SDLOpenglWindowManager::clearScreen(const Color& color)
{
    render->setDrawColor(color);
    render->clear();
}

void SDLOpenglWindowManager::setPincelColor(const Color& color)
{
    render->setDrawColor(color);
}
void SDLOpenglWindowManager::updateScreen()
{
    render->updateScreen();
}
void SDLOpenglWindowManager::setFullScreen()
{
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}
void SDLOpenglWindowManager::setWindowMode()
{
   /// SDL_SetWindowFullscreen(window, 0);
}
void SDLOpenglWindowManager::setSize(const Rect& rect)
{
    if(window!=nullptr)
        SDL_SetWindowSize(window, rect.w, rect.h);
    window_rect.w = rect.w;
    window_rect.h = rect.h;
}
Rect SDLOpenglWindowManager::getWindowDisplayMode(int)
{
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    return Rect{0,0,mode.w,mode.h};
}
void* SDLOpenglWindowManager::getNativeWindowFormatBuffer()
{
    LogOuput(logger_type::Information, "Returning a window");
    return window;
}
} // namespace doengine