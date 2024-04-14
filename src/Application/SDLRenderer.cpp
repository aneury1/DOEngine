#include "SDLRenderer.h"

SDLRenderer::SDLRenderer(SDL_Renderer* nativeRenderer)
    : renderer(nativeRenderer)
{
}

bool SDLRenderer::isRenderOk()
{
    return renderer != NULL;
}

void* SDLRenderer::getNativeRenderer()
{
    return static_cast<void*>(renderer);
}

void SDLRenderer::destroy()
{
    if (isRenderOk())
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}

void SDLRenderer::clear()
{
    SDL_RenderClear(renderer);
}

void SDLRenderer::setDrawColor(doengine::Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void SDLRenderer::present()
{
    SDL_RenderPresent(renderer);
}