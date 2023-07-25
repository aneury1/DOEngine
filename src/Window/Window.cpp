
#include <vector>
#include <sstream>

extern "C" {
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
}

#include "DOEngine.h"
#include <TestState.h>
#include <PlatformState.h>
void Window::_CreateNeededInstance()
{
      fps_handler.reset(new FpsManager());
      gsm.reset(new GameStateManager(this));
      gsm.get()->AddState(1, new TestState(this));
      gsm.get()->AddState(2, new PlatformState(this));
      gsm.get()->SetState(2);
}



Window::Window(int w, int h)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    int flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;
    int res = IMG_Init(flags);
    SDL_Log("sdl_img_flags= %x, IMG_Init result set =%x", flags, res);
    flags = 0x00;
    
    SDL_GetCurrentDisplayMode(1, &mode);
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w,h,SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
    run = render != NULL;
    window_rect.w = w;
    window_rect.h = h;
    Texture::setRender(render);
    _CreateNeededInstance();
}
Window::Window()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GetCurrentDisplayMode(0, &mode);
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w,mode.h,SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
    run = render != NULL;
    window_rect.w = mode.w;
    window_rect.h = mode.h;
    _CreateNeededInstance();
}

void Window::destroy(){
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    render = nullptr;
    window = nullptr;
}

Window::~Window()
{
  destroy();
}

void Window::PollEvent()
{
    fps_handler->Start();
    Event::PollEvent(this);
}
void Window::Update(){
   gsm.get()->Update(Event::timeElapsed);
}
void Window::Render()
{
     SDL_SetRenderDrawColor(render, 255,255,0,255);
     SDL_RenderClear(render);
     gsm.get()->Render();
     SDL_RenderPresent(render);
     fps_handler->Handle();
}


void Window::Quit()
{
  SDL_Log("running will be toggle to false");

  ///destroy();

  this->run = false;
}

const bool Window::IsRunning()const{
    SDL_Log("is Running %ld", run);
   
    return this->run;
}


Window *Window::SetWindowPencilColor(ColorT r, ColorT g, ColorT b, ColorT a){
    SDL_SetRenderDrawColor(render, r,g,b,a);
    return this;
}