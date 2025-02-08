
#include "DOEngine_SDL_includes.h"

#include "FPSManager.h"

namespace doengine
{

void FpsManager::setFPS(long fps)
{
    this->fps = fps;
}
unsigned long FpsManager::getElapsedTime()
{
    return elapsed - start;
}

void FpsManager::Start()
{
    start = SDL_GetTicks();
    elapsed = start;
}

void FpsManager::Handle()
{
    elapsed = SDL_GetTicks();
    long ticks = 1000 / fps;
    if (ticks > (elapsed - start))
    {
        wait = ticks - (elapsed - start);
        SDL_Log("FPS %ld %ld-%ld", wait, elapsed, start);
        if (wait > 0)
            SDL_Delay(wait);
    }
}

} // namespace doengine
