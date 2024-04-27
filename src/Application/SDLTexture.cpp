#include <SDL2/SDL.h>
#include "Application.h"
#include "SDLTexture.h"

SDLTexture::~SDLTexture(){
    if(this_texture)
      SDL_DestroyTexture(this_texture);
    this_texture = nullptr;
}

SDLTexture* SDLTexture::loadFromFile(const char *src){
    auto app = Application::getApplication();
    auto wformat  = (SDL_Window*) app->getWindow()->getNativeWindowFormatBuffer();
    auto nrederer = (SDL_Renderer*)app->getWindow()->getRenderer()->getNativeRenderer();
    
    SDL_Surface *sf = SDL_LoadBMP(src);
    if(!sf){
       valid = false;
       return this;
    }else{
       SDL_Surface *optSf = SDL_ConvertSurface(sf,sf->format, 0);
       if(optSf){
        ////@todo add transparentParameter   SDL_SetColorKey( optSf, SDL_TRUE, SDL_MapRGB( optSf->format, 0xFF, 0xFF, 0xFF ) );
     
        this_texture = SDL_CreateTextureFromSurface(nrederer, optSf);
        
        valid = this_texture != NULL;
        size.x = optSf->w;
        size.y = optSf->h;
         
        SDL_GetTextureColorMod(this_texture, 
          &originalColor.r,
          &originalColor.g,
          &originalColor.b
        );

        SDL_FreeSurface(optSf);
     
       }else{
         valid = false;
       }
    }
    
    SDL_FreeSurface(sf);
  
    return this;
}
bool SDLTexture::validTexture(){
    return valid;
}
void SDLTexture::Draw(const Rect &offset){
    SDL_Rect rect;
    if(!valid)return;
    auto app = Application::getApplication();
    auto wformat  = (SDL_Window*) app->getWindow()->getNativeWindowFormatBuffer();
    auto nrederer = (SDL_Renderer*)app->getWindow()->getRenderer()->getNativeRenderer();
    rect.x = offset.x;
    rect.y = offset.y;
    rect.w = offset.w;
    rect.h = offset.h;
    SDL_RenderCopy(nrederer,this_texture,nullptr, &rect );
}
void SDLTexture::Draw(const Rect &offset, const Rect& clipset){
      SDL_Rect rect;
      SDL_Rect clip;
    if(!valid)return;
    auto app = Application::getApplication();
    auto wformat  = (SDL_Window*) app->getWindow()->getNativeWindowFormatBuffer();
    auto nrederer = (SDL_Renderer*)app->getWindow()->getRenderer()->getNativeRenderer();
    rect.x = offset.x;
    rect.y = offset.y;
    rect.w = offset.w;
    rect.h = offset.h;
    
    clip.x = clipset.x;
    clip.y = clipset.y;
    clip.w = clipset.w;
    clip.h = clipset.h;
    SDL_RenderCopy(nrederer,this_texture,&clip, &rect );
}
void SDLTexture::ModulateColor(const Color& color){}
int SDLTexture::getWidth(){
  return size.x;
}
int SDLTexture::getHeight(){
  size.y;
}