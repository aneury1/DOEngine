
#include "TTFText.h"
#include "Texture.h"

TTFText* TTFText::singleton =nullptr;

void TTFText::setFont(const std::string& path, int fntsize){
	if (TTF_Init()==0)
	{
		TTF_Font* tmp = TTF_OpenFont(path.c_str(), fntsize);
		if (tmp)
		{
			if (this->font)
				TTF_CloseFont(font);
			this->font = tmp;
		}
	}
}
    
    
SDL_Texture *TTFText::createText(const std::string& text, SDL_Renderer *render){
    SDL_Surface *sf = TTF_RenderText_Solid(font,text.c_str(), this->color);
    if(sf)
    {
      SDL_Texture * ret = SDL_CreateTextureFromSurface(render, sf);
      SDL_FreeSurface(sf);
      sf= nullptr;
      return ret;
    }
    return nullptr;
}
    
    
void TTFText::DrawText(const char *text, int x, int y, SDL_Renderer *render){
    Rect  offset={x,y,0,0};
    Rect  clipset{0,0,0,0};
    TTF_SizeText(font,text, &offset.w, &offset.h);
    clipset.w =offset.w;
    clipset.h =offset.h;
    SDL_Texture *text_draw = this->createText(text, render);
    if(text_draw)
        SDL_RenderCopy(render, text_draw, nullptr, &offset);
    SDL_DestroyTexture(text_draw);
    text_draw = nullptr;
}