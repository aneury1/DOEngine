
#include "DOEngine_SDL_includes.h"

#include "FPSManager.h"

namespace doengine
{

void FpsManager::setFPS(long fps)
{
    this->fps = fps;
}

uint32_t FpsManager::getDeltaTime()
{
    return (uint32_t)(elapsed - start);
}

float FpsManager::getElapsedTime()
{
    return (float)(elapsed - start);
}

void FpsManager::Start()
{
    start = SDL_GetTicks();
    frequency = SDL_GetPerformanceFrequency();
    lastCounter = SDL_GetPerformanceCounter();
}

void FpsManager::Handle()
{
    const uint32_t frameDelay = 1000 / fps;

    uint32_t frameTime = SDL_GetTicks() - start;

    if (frameTime < frameDelay)
    {
        SDL_Delay(frameDelay - frameTime);
    }

    start = SDL_GetTicks();
}

void FpsManager::beginFrame()
{
    lastCounter = SDL_GetPerformanceCounter();
}

double FpsManager::endFrame()
{
    uint64_t now = SDL_GetPerformanceCounter();
    double deltaTime =
        static_cast<double>(now - lastCounter) / frequency;

    const double targetFrameTime = 1.0 / fps;

    if (deltaTime < targetFrameTime)
    {
        SDL_Delay(
            static_cast<Uint32>((targetFrameTime - deltaTime) * 1000.0)
        );

        now = SDL_GetPerformanceCounter();
        deltaTime =
            static_cast<double>(now - lastCounter) / frequency;
    }

    return deltaTime;
}

double FpsManager::getTicks()
{
    return SDL_GetTicks();
}


} // namespace doengine