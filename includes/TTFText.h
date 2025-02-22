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

class Texture;
class Renderer;
class TTFText
{

    NativeTextRenderer* nativeRenderer;

  public:
    TTFText();
    void setColor(Color color);
    void setFont(const std::string& path, int fntsize);
    void DrawText(const char* text, int x, int y);
    Texture* createText(const std::string& text);
    void   wrapText(const char* text, int maxWidth, char* wrappedText);
    Texture*  createBitmapFont(const std::string& font_path,const doengine::Color& bg,const doengine::Color& fg);
};

} // namespace doengine