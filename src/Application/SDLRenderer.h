#pragma once

extern "C"
{
#include <SDL2/SDL.h>
}

#include "Renderer.h"

using Renderer = doengine::gfx::Renderer;

class SDLRenderer : public Renderer
{
  public:
    SDLRenderer(SDL_Renderer* nativeRenderer);
    virtual bool isRenderOk() override;
    virtual void* getNativeRenderer() override;
    virtual void destroy() override;
    virtual void clear() override;
    virtual void setDrawColor(doengine::Color) override;
    virtual void present() override;

  private:
    SDL_Renderer* renderer;
};
