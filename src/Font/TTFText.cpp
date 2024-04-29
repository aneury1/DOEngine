#include "TTFText.h"
#include "Renderer.h"    
    

 
TTFText::TTFText()
{
   nativeRenderer = Application::getApplication()->getRender()->getTextRenderer();  
}

void TTFText::setFont(const std::string& path, int fntsize){
      nativeRenderer->setFont(path, fntsize);
}

void TTFText::DrawText(const char* text, int x, int y){
      nativeRenderer->DrawText(text,x,y);
}

Texture* TTFText::createText(const std::string& text){
        return nativeRenderer->createText(text);
}

void TTFText::setForegroundColor(Color color){
   nativeRenderer->setForegroundColor(color);
}
void TTFText::setBackgroundColor(Color color){
      nativeRenderer->setBackgroundColor(color);
}
void TTFText::setFontSize(int fntSize){
      nativeRenderer->setFontSize(fntSize);
}

void TTFText::setColor(Color fg, Color bg){
   nativeRenderer->setColor(fg, bg);
}

void TTFText::getTextSize(std::string text, int *w, int *h){
      nativeRenderer->getTextSize(text,w,h);
}