#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Color.h"
#include "TTFText.h"

class SDLTTFText : public NativeTextRenderer {
   
    Color bg_color;
    Color fg_color;
    TTF_Font *font;
    std::string path;
   
    public:



    virtual void getTextSize(std::string text, int *w, int *h)override;
    virtual void setColor(Color fg, Color bg)override;
    virtual void setFontSize(int fntSize)override;
    virtual void setForegroundColor(Color color)override;
    virtual void setBackgroundColor(Color color) override;
    virtual void setFont(const std::string& path, int fntsize) override;
    virtual void DrawText(const char* text, int x, int y);
    virtual Texture* createText(const std::string& text);
};