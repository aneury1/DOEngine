#include "TTFText.h"
    TTFText::TTFText() : font(NULL)
    {
        color.r = 0xAA;
        color.g = 0xFF;
        color.b = 0xBB;
        color.a = 255;
    }

static TTFText* TTFText::get(){

}

void TTFText::setColor(Color color) {}
    
void TTFText::init() {}
    
void TTFText::destroy() {}
    
void TTFText::setFont(const std::string& path, int fntsize = 23) {}
    
Texture* TTFText::createText(const std::string& text, SDL_Renderer* render){}
    
void TTFText::DrawText(const char* text, int x, int y, SDL_Renderer* render){}
    
void TTFText::drawText(const std::string&, int, int) {}