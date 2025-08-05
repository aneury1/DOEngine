
#include "DOEngine_SDL_includes.h"

#include "FPSManager.h"

namespace doengine
{

void FpsManager::setFPS(long fps)
{
    this->fps = fps;
}
float FpsManager::getDeltaTime()
{
    return deltaTime;
}

void FpsManager::Start()
{
    current = SDL_GetTicks();
    float deltaTime = (current - previous) / 1000.0f;
}

void FpsManager::End()
{
   previous = current;
}

} // namespace doengine