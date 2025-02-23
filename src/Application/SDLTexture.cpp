#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Application.h"
#include "Logger.h"
#include "SDLTexture.h"

namespace doengine
{

namespace
{
bool _initImageSDK()
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
        SDL_Surface* screen = SDL_GetWindowSurface(w);
        SDL_Surface* r = SDL_ConvertSurface(surface, screen->format, 0);
        SDL_FreeSurface(surface);
        surface = nullptr;
        if (r && transparentColor)
        {
            SDL_SetColorKey(r, SDL_TRUE,
                            SDL_MapRGB(r->format, transparentColor->r,
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
        return r;
    }
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
SDL_Texture* ExtractSubTexture(SDL_Renderer* renderer, SDL_Texture* source, SDL_Rect region) {
    if (!source) {
        std::cerr << "Error: Source texture is null!" << std::endl;
        return nullptr;
    }

    // Get the texture format
    Uint32 format;
    int access, width, height;
    SDL_QueryTexture(source, &format, &access, &width, &height);

    // Create a new texture with the same format as the source
    SDL_Texture* subTexture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, region.w, region.h);
    if (!subTexture) {
        std::cerr << "Failed to create subTexture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Set the new texture as the rendering target
    SDL_SetRenderTarget(renderer, subTexture);
    
    // Clear the subTexture with transparency
    SDL_SetTextureBlendMode(subTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);
    
    // Copy the selected region from the source texture
    SDL_RenderCopy(renderer, source, &region, nullptr);
    
    // Reset render target to default
    SDL_SetRenderTarget(renderer, nullptr);

    return subTexture;
}

// Function to copy one texture to another
SDL_Texture* CopyTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture,
                         int width, int height)
{
    // Create a new target texture
    SDL_Texture* targetTexture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET, width, height);
    if (!targetTexture)
    {
        std::cerr << "Failed to create target texture: " << SDL_GetError()
                  << std::endl;
        return nullptr;
    }

    // Set render target to the new texture
    SDL_SetRenderTarget(renderer, targetTexture);

    // Clear the texture (optional)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Copy the source texture to the target texture
    SDL_RenderCopy(renderer, srcTexture, NULL, NULL);

    // Reset render target to default (screen)
    SDL_SetRenderTarget(renderer, NULL);

    return targetTexture;
}

void GetColorMod(SDL_Texture* texture, SDL_Color* color){
    SDL_GetTextureColorMod(texture, &color->r, &color->g, &color->b);
}


} // namespace

SDLTexture::~SDLTexture()
{
    Destroy();
}

SDLTexture::SDLTexture() : NativeTexture()
{
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
    if (valid)
    {
        LogOuput(logger_type::Warning, "For Big texture probably an expensive "
                                       "operation would be triggered");
        SDL_Color tcolor{color.r, color.r, color.b, color.a};
        auto sf = loadSurface(path.c_str(), renderer, &tcolor);
        if (sf)
        {
            this_texture = FreeAndRecreateAtexture(sf, this_texture, renderer);
            GetColorMod(this_texture, &originalColor);
        }
    }
}

SDLTexture* SDLTexture::loadFromFile(const char* src)
{

    auto sf = loadSurface(src, renderer, nullptr);
    if (sf)
    {
        this_texture = FreeAndRecreateAtexture(sf, this_texture, renderer);
        path = src;
        valid = this_texture != nullptr;
        GetColorMod(this_texture, &originalColor);
        SDL_QueryTexture(this_texture, nullptr, nullptr, &size.x, &size.y);
        LogOuput(logger_type::Information,
                 "Is The texture created from SF %d Size[%d, %d]", valid,
                 size.x, size.y);
    }
    return this;
}


NativeTexture* SDLTexture::subTexture(Rect clipset)
{
    SDLTexture* ret = new SDLTexture();
    if (valid)
    {
        ///Todo: Fix bound checks for this function....

        SDL_Rect offset{clipset.x, clipset.y, clipset.w, clipset.h};
        ret->this_texture =
            ExtractSubTexture(renderer, this_texture, offset);
        ret->valid = ret->this_texture != NULL;
        ret->path = this->path;
        ret->size.x = clipset.w;
        ret->size.y = clipset.h;
        GetColorMod(ret->this_texture, &ret->originalColor);

        return ret;
    }

    return this;
}

NativeTexture* SDLTexture::setNativeTexture(void* text)
{
    int w,h;
    Uint32 format;
    int access;
    SDL_Texture* tmp = (SDL_Texture *)text;
    if(tmp==nullptr||SDL_QueryTexture(tmp,&format,&access,&w, &h)!=0){
        LogOuput(logger_type::Error, "Invalid Native Texture Error: %s", SDL_GetError());
        return nullptr;
    }
    Destroy();
    this_texture = CopyTexture(renderer,tmp, w,h);
    valid = this_texture != nullptr;
    size.x = w;
    size.y = h;
    GetColorMod(this_texture, &originalColor);
    return  this;
}

bool SDLTexture::validTexture()
{
    return valid;
}

void SDLTexture::Destroy()
{
    if(valid||this_texture)
    {
        SDL_DestroyTexture(this_texture);
        this_texture = nullptr;
        size.x = size.y = 0;
        valid=false;
    }
}

void SDLTexture::Draw(const Rect& offset)
{
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
    SDL_RenderCopy(renderer, this_texture,  &crect, &rect);
}

void SDLTexture::ModulateColor(const Color& color)
{
    SDL_SetTextureColorMod(this_texture, color.r, color.g, color.b);
}

int SDLTexture::getWidth()
{
    return 0;
}

int SDLTexture::getHeight()
{
    return 0;
}
 

} // namespace doengine