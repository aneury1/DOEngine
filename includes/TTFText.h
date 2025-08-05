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
    void setColor(Color bg, Color fg);
    void setFont(const std::string& path, int fntsize);
    void DrawText(const char* text, int x, int y);
    Texture* createText(const std::string& text);
    void   wrapText(const char* text, int maxWidth, char* wrappedText);
};

} // namespace doengine