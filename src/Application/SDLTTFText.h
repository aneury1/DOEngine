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

class BitmapTextRenderer : public NativeBitmapTextRenderer{
public:


    BitmapTextRenderer();
    ~BitmapTextRenderer();

    // Configuration
    bool setFont(const std::string& fontPath, int fontSize);
    void setColor(SDL_Color color);
    void setLineSpacing(int pixels);
    void setAlignment(Alignment align);

    // Text & layout
    void setText(const std::string& text);
    void setConstraints(int maxWidth, int maxHeight);

    // Pagination API
    void nextPage();
    void prevPage();
    void setPage(size_t page);
    size_t getCurrentPage() const;
    size_t getTotalPages() const;

    // Rendering
    void render(int x, int y);

private:
    struct Line {
        SDL_Texture* texture;
        int width;
        int height;
    };

    void rebuild();
    void clearCache();
    std::vector<std::string> wordWrap(const std::string& text);
    void buildPages(const std::vector<std::string>& lines);

    SDL_Renderer* renderer;
    TTF_Font* font{nullptr};
    SDL_Color color{255, 255, 255, 255};

    std::string text;
    int maxWidth{0};
    int maxHeight{0};
    int lineSpacing{4};
    Alignment alignment{Alignment::Left};

    std::vector<std::vector<Line>> pages;
    size_t currentPage{0};

    bool dirty{true};
};







}; // namespace doengine
