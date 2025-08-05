#include "SDLTexture.h"
#include "Application.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
namespace doengine
{

SDLTexture::~SDLTexture()
{
    if (this_texture)
        SDL_DestroyTexture(this_texture);
    this_texture = nullptr;
}

SDLTexture* SDLTexture::loadFromFile(const char* src)
{
    auto app = Application::getApplication();
    auto wformat = (SDL_Window*)app->getWindow()->getNativeWindowFormatBuffer();
    auto nrederer =
        (SDL_Renderer*)app->getWindow()->getRenderer()->getNativeRenderer();

    SDL_Surface* sf = IMG_Load(src);
    if (!sf)
    {
        valid = false;
        return this;
    }
    else
    {
        SDL_Surface* optSf = SDL_ConvertSurface(sf, sf->format, 0);
        if (optSf)
        {
            ////@todo add transparentParameter   SDL_SetColorKey( optSf,
            /// SDL_TRUE, SDL_MapRGB( optSf->format, 0xFF, 0xFF, 0xFF ) );

            this_texture = SDL_CreateTextureFromSurface(nrederer, optSf);

            valid = this_texture != NULL;
            size.x = optSf->w;
            size.y = optSf->h;

            SDL_GetTextureColorMod(this_texture, &originalColor.r,
                                   &originalColor.g, &originalColor.b);

            SDL_FreeSurface(optSf);
        }
        else
        {
            valid = false;
        }
    }

    SDL_FreeSurface(sf);

    return this;
}
bool SDLTexture::validTexture()
{
    return valid;
}
void SDLTexture::Draw(const Rect& offset)
{
    SDL_Rect rect;
   /// if (!valid)
    ///    return;
    auto app = Application::getApplication();
    auto wformat = (SDL_Window*)app->getWindow()->getNativeWindowFormatBuffer();
    auto nrederer =
        (SDL_Renderer*)app->getWindow()->getRenderer()->getNativeRenderer();
    rect.x = offset.x;
    rect.y = offset.y;
    rect.w = offset.w;
    rect.h = offset.h;
   int ret = SDL_RenderCopy(nrederer, this_texture, nullptr, &rect);
   
}
void SDLTexture::Draw(const Rect& offset, const Rect& clipset)
{
    SDL_Rect rect;
    SDL_Rect clip;
    if (!valid)
        return;
    auto app = Application::getApplication();
    auto wformat = (SDL_Window*)app->getWindow()->getNativeWindowFormatBuffer();
    auto nrederer =
        (SDL_Renderer*)app->getWindow()->getRenderer()->getNativeRenderer();
    rect.x = offset.x;
    rect.y = offset.y;
    rect.w = offset.w;
    rect.h = offset.h;

    clip.x = clipset.x;
    clip.y = clipset.y;
    clip.w = clipset.w;
    clip.h = clipset.h;
    int ret = SDL_RenderCopy(nrederer, this_texture, &clip, &rect);
}
void SDLTexture::ModulateColor(const Color& color)
{
}
int SDLTexture::getWidth()
{
    return size.x;
}
int SDLTexture::getHeight()
{
    return size.y;
}

NativeTexture* SDLTexture::subTexture(Rect clipset)
{
    auto app = Application::getApplication();
    auto wformat = (SDL_Window*)app->getWindow()->getNativeWindowFormatBuffer();
    auto nrederer =
        (SDL_Renderer*)app->getWindow()->getRenderer()->getNativeRenderer();
    SDL_Texture* targetTexture =
        SDL_CreateTexture(nrederer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET, clipset.w, clipset.h);
    if (!targetTexture)
    {
        SDL_Log("Failed to create target texture: %s", SDL_GetError());
        return this;
    }
    SDL_SetRenderTarget(nrederer, targetTexture);
    SDL_SetRenderDrawColor(nrederer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderClear(nrederer);
    SDL_Rect rect;
    rect.x = clipset.x;
    rect.y = clipset.y;
    rect.w = clipset.w;
    rect.h = clipset.h;
    SDL_RenderCopy(nrederer, this_texture, &rect, NULL);
    SDL_SetRenderTarget(nrederer, NULL);

    SDLTexture* retTexture = new SDLTexture();
    retTexture->this_texture = targetTexture;

    return (NativeTexture*)retTexture;
}

} // namespace doengine