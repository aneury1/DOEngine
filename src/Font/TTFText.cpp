#include "TTFText.h"
#include "Renderer.h"    
    
TTFText::TTFText()  
{ 
}

TTFText* TTFText::get(){
   static TTFText *singleton = new TTFText();
   return singleton;
}

void TTFText::setColor(Color color) {}
    
void TTFText::init() {}
    
void TTFText::destroy() {}
    
void TTFText::setFont(const std::string& path, int fntsize) {}
    
Texture* TTFText::createText(const std::string& text){}
    
void TTFText::DrawText(const char* text, int x, int y){}
    
void TTFText::drawText(const std::string&, int, int) {}