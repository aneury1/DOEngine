
#include <sstream>
#include <vector>
#include <iostream>
#include <string_view>

#include "Application.h"

Application *Application::applicationObject = nullptr;

Application::Application()
{
    const int rc = SDL_Init(SDL_INIT_EVERYTHING);

    if (rc != 0)
    {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return;
    }
  
}

void Application::destroy()
{
    render->destroy();
    SDL_DestroyWindow(window);
    render = nullptr;
    window = nullptr;
}

Application::~Application()
{
    destroy();
}

void Application::setFullScreen()
{
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Application::setWindowMode()
{
    SDL_SetWindowFullscreen(window, 0);
}
void Application::PollEvent()
{
    fps_handler->Start();
    Event::PollEvent();
}

void Application::Update()
{
    gsm.get()->Update(Event::timeElapsed);
}

void Application::Render()
{
    render->setDrawColor({0, 0, 0, 255});
    render->clear();
    gsm.get()->Render();
    render->present();
    fps_handler->Handle();
  
}

void Application::Quit()
{
   run = false;    
}

const bool Application::IsRunning() const
{
    return run;
}

void Application::SetWindowPencilColor(doengine::Color color)
{
    SDL_SetRenderDrawColor(
        static_cast<SDL_Renderer*>(render->getNativeRenderer()), color.r,
        color.g, color.b, color.a);
}