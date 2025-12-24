#include "Logger.h"
#include "SDLOpenglWindowManager.h"
#include "SDLOpenglRenderer.h"
#include <GL/gl.h>
//// g++ ./SDL2O.cpp -lSDL2 -lGL

namespace doengine
{
 
SDLOpenglWindowManager::SDLOpenglWindowManager()
{
    
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

    window = SDL_CreateWindow("  ", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, window_rect.w, window_rect.h,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS |SDL_WINDOW_OPENGL);

    this->support_opengl = true;
       
    this->render = new SDLOpenglRenderer(window);
    
    LogOuput(logger_type::Information, "SDL Created Window %s", SDL_GetError());
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);


    LogOuput(logger_type::Information, "SDL Created Window %s", SDL_GetError());


    SDLWindowManager::setSize(window_rect);
    

    this->createWindow();
    
    LogOuput(logger_type::Information, "SDL Created Window %s", SDL_GetError());
    
    run = render->isRenderOk();
    
    LogOuput(logger_type::Information, "SDL Created Window %s", SDL_GetError());
}


SDLOpenglWindowManager::~SDLOpenglWindowManager()
{
}

bool SDLOpenglWindowManager::createWindow(const Rect& rect)
{
    initEngine();
    return run;
}

bool SDLOpenglWindowManager::createWindow()
{
    initEngine();
    return run;
}

Renderer* SDLOpenglWindowManager::getRenderer()
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
Rect SDLOpenglWindowManager::getWindowDisplayMode(int m)
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