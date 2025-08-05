#include "TTFText.h"
#include "Renderer.h"
namespace doengine
{
TTFText::TTFText()
{
    nativeRenderer =
        Application::getApplication()->getRender()->getTextRenderer();
}

void TTFText::setColor(Color color)
{
    nativeRenderer->setColor(color);
}

void TTFText::setColor(Color bg, Color fg)
{
    nativeRenderer->setColor(fg, bg);

}

void TTFText::setFont(const std::string& path, int fntsize)
{
    nativeRenderer->setFont(path, fntsize);
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
 

} // namespace doengine