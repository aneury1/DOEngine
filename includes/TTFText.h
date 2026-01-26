#pragma once
#include <string>

#include "Application.h"
#include "Color.h"
#include "DOEngine.h"
#include "Geometric.h"
#include "Texture.h"

using std::string;

namespace doengine
{
class NativeBitmapTextRenderer;
class NativeTextRenderer;
class Texture;
class Renderer;
class TTFText
{

    NativeTextRenderer* nativeRenderer;
    NativeBitmapTextRenderer* nativeBitmapRenderer;

  public:
    TTFText();
    void setColor(Color color);
    void setForegroundColor(const Color& color);
    void setFont(const std::string& path, int fntsize);
    void DrawText(const char* text, int x, int y);
    void DrawText(int x, int y, const char *fmt, ...);
    Texture* createText(const std::string& text);
    void   wrapText(const char* text, int maxWidth, char* wrappedText);
    Texture*  createBitmapFont(const std::string& font_path,const doengine::Color& bg,const doengine::Color& fg);

    int getFontHeight();
};

} // namespace doengine

