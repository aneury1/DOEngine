
#include <sstream>
#include <vector>
#include <iostream>
#include <string_view>

#include "Application.h"
#include "Event.h"


Application *Application::applicationObject = nullptr;


Application::Application()
{
  windowManager =  WindowManager::getWindowManager();
  gsm = new GameStateManager();
}

void Application::destroy()
{
    //render->destroy();
    //SDL_DestroyWindow(window);
    //render = nullptr;
    //window = nullptr;
}

Application::~Application()
{
    destroy();
}

void Application::setFullScreen()
{
    windowManager->setFullScreen();
}

void Application::setWindowMode()
{
   windowManager->setFullScreen();
}
void Application::PollEvent()
{
    //fps_handler->Start();
    Event::PollEvent();
}

void Application::Update()
{
    gsm->Update(Event::timeElapsed);
}

void Application::Render()
{
    gsm->Render();
    windowManager->updateScreen();
}

void Application::Quit()
{
   run = false;    
}

const bool Application::IsRunning() const
{
    return run;
}

void Application::SetWindowPencilColor(const Color& color)
{
   windowManager->setPincelColor(color);
}
void Application::clearScreen(const Color& color){
    windowManager->clearScreen(color);
}

void Application::createWindow(const Rect& rect){
   run = windowManager->createWindow(rect);
}