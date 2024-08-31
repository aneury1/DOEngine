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

} // namespace doengine