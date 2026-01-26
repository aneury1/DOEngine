
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

#include "Application.h"
#include "Event.h"

namespace doengine
{
Application* Application::applicationObject = nullptr;

Application::Application()
{
    windowManager = WindowManager::getWindowManager();
    gsm = new GameStateManager();
    fps_handler = new FpsManager();
    fps_handler->setFPS(60);
}

void Application::destroy()
{
    // render->destroy();
    // SDL_DestroyWindow(window);
    // render = nullptr;
    // window = nullptr;
}

Application::~Application()
{
    destroy();
}

void Application::_internalResize()
{
    windowManager->setSize(Rect{window_rect.w, window_rect.h});
}

void Application::setFullScreen()
{
    windowManager->setFullScreen();
}

void Application::setWindowMode()
{
    windowManager->setWindowMode();
}
void Application::PollEvent()
{
    fps_handler->Start();
    fps_handler->beginFrame();
    Event::PollEvent();
}

void Application::Update()
{
    auto deltaTime = fps_handler->endFrame();
    gsm->Update(deltaTime);
}

void Application::Render()
{
    gsm->Render();
    windowManager->updateScreen();
    fps_handler->Handle();
}

void Application::Quit()
{
    run = false;
}
WindowManager* Application::getWindow()
{
    return windowManager;
}
Renderer* Application::getRender() const
{
    return windowManager->getRenderer();
}

const bool Application::IsRunning() const
{
    /// LogOuput(logger_type::Information, "Is running %d", run);
    return run;
}

long Application::getElapsedTime()
{
    return fps_handler->getElapsedTime();
}

uint32_t Application::getDeltaTime()
{
    return fps_handler->getDeltaTime();
}

void Application::setW(int w)
{
    window_rect.w = w;
    _internalResize();
}
void Application::setH(int h)
{
    window_rect.h = h;
    _internalResize();
}
void Application::setSize(int w, int h)
{
    window_rect.w = w;
    window_rect.h = h;
    _internalResize();
}
int Application::getH()
{
    return window_rect.h;
}
int Application::getW()
{
    return window_rect.w;
}

Rect Application::getDisplayMode(int m)
{
    return windowManager->getWindowDisplayMode(m);
}

void Application::SetWindowPencilColor(const Color& color)
{
    windowManager->setPincelColor(color);
}
void Application::clearScreen(const Color& color)
{
    windowManager->clearScreen(color);
}

void Application::createWindow(const Rect& rect)
{
    this->setW(rect.w);
    this->setH(rect.h);
    run = windowManager->createWindow(rect);
}

void Application::addState(GameState* state, int id)
{
    gsm->AddState(id, state);
}

void Application::setState(int id)
{
    gsm->SetState(id);
}

} // namespace doengine