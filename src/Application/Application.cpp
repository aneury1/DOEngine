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

#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

#include "Application.h"
#include "Event.h"

namespace doengine
{

Application::Application()
{
    windowManager = WindowManager::getWindowManager();
    gsm = std::make_shared<GameStateManager>();
    fps_handler = std::make_shared<FpsManager>();
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
    if (windowManager)
        windowManager->setSize(Rect{window_rect.w, window_rect.h});
    else
        LogOuput(logger_type::Error, "Window Manager is nullptr");
}

void Application::setFullScreen()
{
    if (windowManager)
        windowManager->setFullScreen();
    else
        LogOuput(logger_type::Error, "Window Manager is nullptr");
}

void Application::setWindowMode()
{
    if (windowManager)
        windowManager->setWindowMode();
    else
        LogOuput(logger_type::Error, "Window Manager is nullptr");
}
void Application::PollEvent()
{
    if (fps_handler)
    {
        fps_handler->Start();
        fps_handler->beginFrame();
    }
    else
    {
        LogOuput(logger_type::Error, "Fps Handler is nullptr");
    }
    Event::PollEvent();
}

void Application::Update()
{
    if (fps_handler)
    {
        auto deltaTime = fps_handler->endFrame();
        gsm->Update(deltaTime);
    }
    else
    {
        LogOuput(logger_type::Error, "Fps Handler is nullptr");
    }
}

void Application::Render()
{
    /// gsm->Render();
    /// windowManager->updateScreen();
    /// fps_handler->Handle();
}

void Application::Quit()
{
    run = false;
    gsm->RemoveState(gsm->GetCurrentState());
}
std::shared_ptr<WindowManager> Application::getWindow()
{
    return windowManager;
}
std::shared_ptr<doengine::Renderer> Application::getRender() const
{
    return windowManager->getRenderer();
}

bool Application::IsRunning() const
{
    LogOuput(logger_type::Information, "Is running %d", run);
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
    LogOuput(logger_type::Information, "CREATE WINDOW SUCCESS.");
}

void Application::addState(GameState* state, int id)
{
  ////  gsm->AddState(id, state);
}

void Application::setState(int id)
{
 /////   gsm->SetState(id);
}

} // namespace doengine