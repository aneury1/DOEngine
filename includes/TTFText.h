#pragma once
#include <string>

#include "DOEngine.h"
#include "Geometric.h"
#include "Font.h"

class Texture;

class Renderer;

class TTFText : public Font
{

  TTFText();
  static TTFText* singleton;

  public:
    static TTFText* get();
    void setColor(Color color) override;
    void init() override;
    void destroy() override;
    void setFont(const std::string& path, int fntsize = 23) override;
    Texture* createText(const std::string& text);
    void DrawText(const char* text, int x, int y);
    void drawText(const std::string&, int, int) override;
};