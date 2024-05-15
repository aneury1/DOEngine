#include <SDL2/SDL_ttf.h>
#include "Application.h"
#include "SDLTTFText.h"



void SDLTTFText::setColor(Color fg, Color bg){
   this->fg_color = fg;
   this->bg_color = bg;
}

void SDLTTFText::setForegroundColor(Color color){
    this->fg_color = color;
}
void SDLTTFText::setBackgroundColor(Color color){
    this->bg_color = color;
}

void SDLTTFText::setFontSize(int fntSize){
    if(font)
        TTF_SetFontSize(font, fntSize);
}


void SDLTTFText::setFont(const std::string& path, int fntsize){
    if(font!=nullptr){
        TTF_CloseFont(font);
        font= nullptr;
    }
    font = TTF_OpenFont(path.c_str(), fntsize);
    if(font){
        this->path = path;
    }
}
void SDLTTFText::DrawText(const char* text, int x, int y){
    auto renderer = Application::getApplication()->getRender();
    auto nativeRenderer = (SDL_Renderer *)renderer->getNativeRenderer();
    SDL_Color bg;
    bg.a = bg_color.a;
    bg.r = bg_color.r;
    bg.b = bg_color.b;
    bg.g = bg_color.g;
    SDL_Color scolor;
    scolor.r = fg_color.r;
    scolor.g = fg_color.g;
    scolor.b = fg_color.b;
    scolor.a = fg_color.a;
    SDL_Surface *sf = TTF_RenderText(font, text,scolor,bg);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(nativeRenderer,sf);
    if(texture){
        SDL_Rect offset;
        offset.x = x;
        offset.y = y;
        SDL_QueryTexture(texture, NULL,NULL,&offset.w, &offset.h);
        SDL_RenderCopy(nativeRenderer,texture,NULL,&offset);
        
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(sf);
        texture = nullptr;
        sf= nullptr;
    }else{
      ///  DO_DEBUG("cANT REDNER FONT???");
    }
    
}
void SDLTTFText::getTextSize(const std::string& text, int *w, int *h){
  if(font)
    TTF_SizeText(font, text.c_str(), w, h);
}

Texture* SDLTTFText::createText(const std::string& text){}