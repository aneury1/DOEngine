#pragma once

#include "DOEngine_SDL_includes.h"
#include <string>
#include <unordered_map>

#include "Color.h"
#include "NativeStructs.h"
#include "TTFText.h"

using std::string;

namespace doengine
{

class SDLTTFText : public NativeTextRenderer
{

    std::unordered_map<char, GlyphInfo> glyphs;
    int glyph_height;
    Color bg_color;
    Color fg_color;
    TTF_Font* font;
    string path;
    Texture *glyphTexture = nullptr;
    SDL_Texture *glyph_texture;

  public:
    SDLTTFText();
    virtual ~SDLTTFText();
    virtual void setColor(Color fg, Color bg) override;
    virtual void setColor(Color color) override;
    virtual void setFontSize(int fntSize) override;
    virtual void setForegroundColor(Color color) override;
    virtual void setBackgroundColor(Color color) override;
    virtual void setFont(const std::string& path, int fntsize) override;
    virtual void DrawText(const char* text, int x, int y);
    virtual Texture* createText(const std::string& text);
    virtual void getTextSize(const std::string& text, int* w, int* h);
    virtual void wrapText(const char* text, int maxWidth, char* wrappedText);
    virtual Texture* createBitmapFont(const std::string& font_path,const doengine::Color& bg,const doengine::Color& fg)override;
    virtual int getFontHeight() override;
    virtual Rect getTextSize(const char* str) override;


    Texture* createGlyph();
    bool DrawTextByGlyphs(int x, int y, const std::string& text, int max_width = -1);
};

}; // namespace doengine
