#include <stdarg.h>
#include "TTFText.h"
#include "Renderer.h"
#include "Logger.h"
namespace doengine
{
TTFText::TTFText()
{
    LogOuput(logger_type::Information,"--TTFText--");
    nativeRenderer =
        Application::getApplication()->getRender()->getTextRenderer();
}

void TTFText::setColor(Color color)
{
    nativeRenderer->setColor(color);
}

void TTFText::setFont(const std::string& path, int fntsize)
{
  LogOuput(logger_type::Information,"TTFText::setFont FontSRc=%s", path.c_str());
  nativeRenderer->setFont(path, fntsize);
}

void TTFText::setForegroundColor(const Color& color)
{
   nativeRenderer->setForegroundColor(color);
}

void TTFText::DrawText(int x, int y, const char *fmt, ...)
{
    // Start variable argument handling
    va_list args;
    va_start(args, fmt);

    // Buffer for formatted message
    char buffer[4096];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    // End argument handling
    va_end(args);
    this->DrawText(buffer,x,y);
}

void TTFText::DrawText(const char* text, int x, int y)
{
    nativeRenderer->DrawText(text, x, y);
}

Texture* TTFText::createText(const std::string& text)
{
    return nativeRenderer->createText(text);
}

void TTFText::wrapText(const char* text, int maxWidth, char* wrappedText)
{
    nativeRenderer->wrapText(text,maxWidth,wrappedText);
    return ;
}

Texture* TTFText::createBitmapFont(const std::string& font_path,const doengine::Color& bg,const doengine::Color& fg){
  
  if(nativeRenderer){
    LogOuput(logger_type::Information,"Create Bitmap font");
    return nativeRenderer->createBitmapFont(font_path,bg,fg);
  }
  return nullptr;
}

int TTFText::getFontHeight()
{
  if(nativeRenderer){
    LogOuput(logger_type::Information,"Create Bitmap font");
    return nativeRenderer->getFontHeight();
  }
  return 0;
}


} // namespace doengine