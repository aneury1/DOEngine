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

#include "DOEngine_SDL_includes.h"
#include <iostream>

#include "Application.h"
#include "Logger.h"
#include "SDLTexture.h"

namespace doengine
{

namespace
{
[[maybe_unused]] bool _initImageSDK()
{
    int flags = IMG_INIT_AVIF | IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP |
                IMG_INIT_TIF | IMG_INIT_JXL;
    int ret = IMG_Init(flags);
    return (ret & flags) == flags;
}

SDL_Surface* loadSurface(const char* src, SDL_Renderer* r,
                         SDL_Color* transparentColor)
{
    SDL_Surface* surface = IMG_Load(src);
    LogOuput(logger_type::Information, "After try load surface");
    SDL_Window* w = SDL_RenderGetWindow(r);
    if (surface && w)
    {
        LogOuput(logger_type::Information, "Surface and Window Ready");
        /// SDL_Surface* screen = SDL_GetWindowSurface(w);
        //// SDL_Surface* r = SDL_ConvertSurface(surface, screen->format, 0);
        /// SDL_FreeSurface(surface);
        auto sf = surface;
        surface = nullptr;
        if (sf && transparentColor)
        {
            SDL_SetColorKey(sf, SDL_TRUE,
                            SDL_MapRGB(sf->format, transparentColor->r,
                                       transparentColor->g,
                                       transparentColor->b));
            LogOuput(logger_type::Information,
                     "Image loaded With transparency");
        }
        else
        {
            LogOuput(logger_type::Information,
                     "Image loaded Without transparency");
        }
        return sf;
    }

    if (surface)
        SDL_FreeSurface(surface);

    return nullptr;
}

SDL_Texture* FreeAndRecreateAtexture(SDL_Surface* sf, SDL_Texture* this_texture,
                                     SDL_Renderer* renderer)
{
    if (sf)
    {
        LogOuput(logger_type::Information, "Surface is OK");

        if (this_texture)
        {
            LogOuput(logger_type::Information, "Needs To Destroy Texture");
            SDL_DestroyTexture(this_texture);
            this_texture = nullptr;
        }
        this_texture = SDL_CreateTextureFromSurface(renderer, sf);
        LogOuput(logger_type::Information, "Is The texture created from SF %d",
                 this_texture != NULL);
        SDL_FreeSurface(sf);
        sf = nullptr;
        return this_texture;
    }
    else
    {
        /// Nothing todo add logs to debug.
    }
    return nullptr;
}

// Function to extract a subtexture
SDL_Texture* ExtractSubTexture(SDL_Renderer* renderer, SDL_Texture* source,
                               SDL_Rect region)
{
    if (!renderer || !source)
    {
        LogOuput(logger_type::Information,
                 "Source Texture or Renderer is null");
        return nullptr;
    }

    // Save renderer state
    SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);

    Uint32 format;
    int access, width, height;
    SDL_QueryTexture(source, &format, &access, &width, &height);

    // Create target texture
    SDL_Texture* subTexture = SDL_CreateTexture(
        renderer, format, SDL_TEXTUREACCESS_TARGET, region.w, region.h);

    if (!subTexture)
    {
        std::cerr << "Failed to create subTexture: " << SDL_GetError()
                  << std::endl;
        return nullptr;
    }

    SDL_SetTextureBlendMode(subTexture, SDL_BLENDMODE_BLEND);

    // Render into subTexture
    SDL_SetRenderTarget(renderer, subTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, source, &region, nullptr);

    // Restore renderer target
    SDL_SetRenderTarget(renderer, oldTarget);

    return subTexture;
}

// Function to copy one texture to another
SDL_Texture* CopyTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture,
                         int width, int height)
{
    if (!renderer || !srcTexture)
        return nullptr;
    SDL_Color colorMod;
    // Save renderer state
    SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);

    SDL_BlendMode oldBlend;
    SDL_GetTextureBlendMode(srcTexture, &oldBlend);

    Uint8 r, g, b, a;
    SDL_GetTextureColorMod(srcTexture, &r, &g, &b);
    SDL_GetTextureAlphaMod(srcTexture, &a);

    // Create target texture
    SDL_Texture* targetTexture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET, width, height);

    if (!targetTexture)
    {
        // SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        //              "Failed to create target texture: %s", SDL_GetError());
        return nullptr;
    }

    SDL_SetTextureBlendMode(targetTexture, SDL_BLENDMODE_BLEND);

    // Apply color modulation if requested
    {
        /// SDL_SetTextureColorMod(srcTexture, colorMod.r, colorMod.g,
        ///                         colorMod.b);
        ///  SDL_SetTextureAlphaMod(srcTexture, colorMod.a);
    }

    // Render to target
    SDL_SetRenderTarget(renderer, targetTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, srcTexture, nullptr, nullptr);

    // Restore renderer + texture state
    SDL_SetRenderTarget(renderer, oldTarget);
    SDL_SetTextureBlendMode(srcTexture, oldBlend);
    SDL_SetTextureColorMod(srcTexture, r, g, b);
    SDL_SetTextureAlphaMod(srcTexture, a);

    return targetTexture;
}

void GetColorMod(SDL_Texture* texture, SDL_Color* color)
{
    if (!texture)
        return;
    SDL_GetTextureColorMod(texture, &color->r, &color->g, &color->b);
    SDL_GetTextureAlphaMod(texture, &color->a);
}

} // namespace

SDLTexture::~SDLTexture()
{
    Destroy();
}

SDLTexture::SDLTexture() : NativeTexture()
{
    if (!Application::getApplication()->IsRunning())
    {
        valid = false;
        this_texture = nullptr;
        size.x = 0;
        size.y = 0;
        originalColor.r = 255;
        originalColor.g = 255;
        originalColor.b = 255;
        originalColor.a = 0;
        renderer = nullptr;
    }
    renderer = (SDL_Renderer*)Application::getApplication()
                   ->getRender()
                   ->getNativeRenderer();
    valid = false;
    this_texture = nullptr;
    size.x = 0;
    size.y = 0;
    originalColor.r = 255;
    originalColor.g = 255;
    originalColor.b = 255;
    originalColor.a = 0;
}

void SDLTexture::SetTransparentColor(const Color& color)
{
    if (valid && Application::getApplication()->IsRunning())
    {
        LogOuput(logger_type::Warning, "For Big texture probably an expensive "
                                       "operation would be triggered");
        SDL_Color tcolor{color.r, color.g, color.b, color.a};
        auto sf = loadSurface(path.c_str(), renderer, &tcolor);
        if (sf)
        {
            this_texture = FreeAndRecreateAtexture(sf, this_texture, renderer);
            GetColorMod(this_texture, &originalColor);
        }
    }
}

std::shared_ptr<NativeTexture> SDLTexture::loadFromFile(const char* src)
{
    if (!Application::getApplication()->IsRunning())
    {
        valid = false;
        return shared_from_this();
    }

    auto sf = loadSurface(src, renderer, nullptr);
    if (sf)
    {
        SDL_Log("loading this texture=%s", src);
        this_texture = FreeAndRecreateAtexture(sf, this_texture, renderer);
        if (this_texture)
            return shared_from_this();
        path = src;
        valid = this_texture != nullptr;
        SDL_Log("loading this texture=>%s valid=>%d", src, valid);
        GetColorMod(this_texture, &originalColor);
        SDL_QueryTexture(this_texture, nullptr, nullptr, &size.x, &size.y);
    }
    return shared_from_this();
}

std::shared_ptr<NativeTexture> SDLTexture::subTexture(Rect clipset)
{
    std::shared_ptr<SDLTexture> ret = std::make_shared<SDLTexture>();
    if (valid)
    {
        /// Todo: Fix bound checks for this function....
        /// Todo: Fix bound checks for this function....

        SDL_Rect offset{clipset.x, clipset.y, clipset.w, clipset.h};
        ret->this_texture = ExtractSubTexture(renderer, this_texture, offset);
        ret->this_texture = ExtractSubTexture(renderer, this_texture, offset);
        ret->valid = ret->this_texture != NULL;
        ret->path = this->path;
        ret->size.x = clipset.w;
        ret->size.y = clipset.h;
        GetColorMod(ret->this_texture, &ret->originalColor);

        return ret;
    }

    return shared_from_this();
}

void* SDLTexture::getNativeBuffer()
{
    return this_texture;
}

std::shared_ptr<NativeTexture> SDLTexture::setNativeTexture(void* text)
{
    int w, h;
    Uint32 format;
    int access;
    if (!Application::getApplication()->IsRunning())
    {
        valid = false;
        return shared_from_this();
    }

    SDL_Texture* tmp = (SDL_Texture*)text;
    if (tmp == nullptr || SDL_QueryTexture(tmp, &format, &access, &w, &h) != 0)
    {
        LogOuput(logger_type::Error, "Invalid Native Texture Error: %s",
                 SDL_GetError());
        return shared_from_this();
    }
    Destroy();
    this_texture = CopyTexture(renderer, tmp, w, h);
    this_texture = CopyTexture(renderer, tmp, w, h);
    valid = this_texture != nullptr;
    size.x = w;
    size.y = h;
    GetColorMod(this_texture, &originalColor);
    return shared_from_this();
}

bool SDLTexture::validTexture()
{
    LogOuput(logger_type::Error, "validTexture: %d", valid);
    return valid;
}

void SDLTexture::Destroy()
{
    if (valid || this_texture)
    if (valid || this_texture)
    {
        SDL_DestroyTexture(this_texture);
        this_texture = nullptr;
        size.x = size.y = 0;
        valid = false;
        valid = false;
    }
}

void SDLTexture::Draw(int x, int y)
{
    if(!renderer)return;
    SDL_Rect rect{x, y, this->size.x, this->size.y};
    SDL_RenderCopy(renderer, this_texture, NULL, &rect);
}

void SDLTexture::Draw(const Rect& offset)
{
    if (!Application::getApplication()->IsRunning())
        return;
    if (!renderer && !Application::getApplication()->getRender())
    {
        return;
    }
    else if (!renderer && Application::getApplication()->getRender())
    {
        renderer = (SDL_Renderer*)Application::getApplication()
                       ->getRender()
                       ->getNativeRenderer();
    }
    SDL_Rect rect{
        offset.x,
        offset.y,
        offset.w,
        offset.h,
    };
    SDL_RenderCopy(renderer, this_texture, NULL, &rect);
}

void SDLTexture::Draw(const Rect& offset, const Rect& clipset)
{
    if (!Application::getApplication()->IsRunning())
        return;
    if (!renderer && !Application::getApplication()->getRender())
    {
        return;
    }
    else if (!renderer && Application::getApplication()->getRender())
    {
        renderer = (SDL_Renderer*)Application::getApplication()
                       ->getRender()
                       ->getNativeRenderer();
    }
    SDL_Rect rect{
        offset.x,
        offset.y,
        offset.w,
        offset.h,
    };
    SDL_Rect crect{
        clipset.x,
        clipset.y,
        clipset.w,
        clipset.h,
    };
    SDL_RenderCopy(renderer, this_texture, &crect, &rect);
}

void SDLTexture::Draw(const Rect& offset, const Rect& clipset,
                      const double angle)
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

    SDL_RenderCopyEx(nrederer, this_texture, &clip, &rect, angle, nullptr,
                     SDL_FLIP_NONE);
}

void SDLTexture::Draw(const Rect& offset, const Rect& clipset,
                      const double angle, const Point& center)
{
    SDL_Rect rect;
    SDL_Rect clip;
    SDL_Point center_point;
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

    center_point.x = center.x;
    center_point.y = center.y;

    SDL_RenderCopyEx(nrederer, this_texture, &clip, &rect, angle, &center_point,
                     SDL_FLIP_NONE);
}

void SDLTexture::ModulateColor(const Color& color)
{
    if (this_texture)
        SDL_SetTextureColorMod(this_texture, color.r, color.g, color.b);
}

int SDLTexture::getWidth()
{
    return this->size.x;
}

int SDLTexture::getHeight()
{
    return this->size.y;
    return this->size.y;
}


} // namespace doengine
