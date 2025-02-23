
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
}

void FpsManager::Handle()
{
    elapsed = SDL_GetTicks();
    uint32_t ticks = 1000 / fps;
    if (ticks > (elapsed - start))
    {
        wait =  ticks - (elapsed - start);
        ////SDL_Log("FPS %ld", wait);
        if (wait > 0)
            SDL_Delay(wait);
        start = elapsed;
    } 
}

} // namespace doengine