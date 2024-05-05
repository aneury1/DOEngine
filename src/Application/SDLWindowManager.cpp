#include <SDL2/SDL_ttf.h>
#include "SDLWindowManager.h"



bool SDLWindowManager::createWindow(){
    SDL_Init(SDL_INIT_EVERYTHING);     
        
    SDL_DisplayMode mode;

    SDL_GetCurrentDisplayMode(0, &mode);

    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
       
    render= (new SDLRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)));
    
    run = render->isRenderOk();
    
    window_rect.w = mode.w;
    
    window_rect.h = mode.h;

    return run;
}
 
bool SDLWindowManager::createWindow(const Rect& rect){
        
    SDL_Init(SDL_INIT_EVERYTHING);     
        
    SDL_GetCurrentDisplayMode(0, &mode);
    
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, rect.w, rect.h, SDL_WINDOW_SHOWN /*| SDL_WINDOW_BORDERLESS*/);
       
    render= (new SDLRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)));

    TTF_Init();
    
    run = render->isRenderOk();
    
    window_rect.w = rect.w;
    
    window_rect.h = rect.h;

    return run;
}

bool SDLWindowManager::isValid(){
   return run;
}

void SDLWindowManager::setPincelColor(const Color& color){
   SDL_SetRenderDrawColor((SDL_Renderer *)render->getNativeRenderer(), color.r, color.g, color.b, 255 );
}

void SDLWindowManager::clearScreen(const Color& color){
   SDL_SetRenderDrawColor((SDL_Renderer *)render->getNativeRenderer(), color.r, color.g, color.b, 255 );
   SDL_RenderClear((SDL_Renderer *)render->getNativeRenderer());
}

void SDLWindowManager::updateScreen(){
  SDL_RenderPresent((SDL_Renderer *)render->getNativeRenderer());
}
Renderer* SDLWindowManager::getRenderer(){
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
void SDLWindowManager::setSize(const Rect& rect){
   SDL_SetWindowSize(window, rect.w, rect.h);
   window_rect.w= rect.w;
   window_rect.h = rect.h;
 }

void *SDLWindowManager::getNativeWindowFormatBuffer(){
   return (void *)window;
}