/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */


#pragma once
#include <memory>
#include "DOEngine_SDL_includes.h"
#include <string>
#include <unordered_map>

#include "Color.h"
#include "NativeStructs.h"
#include "TTFText.h"

namespace doengine
{

class SDLTTFText : public NativeTextRenderer
{
    std::weak_ptr<Application> app;
    std::unordered_map<char, GlyphInfo> glyphs;
    int glyph_height = 0;
    Color bg_color;
    Color fg_color;
    TTF_Font* font;
    std::string path;
    std::shared_ptr<Texture> glyphTexture = nullptr;
    SDL_Texture* glyph_texture = nullptr;

    bool checkAppIsRunning();

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
    virtual std::shared_ptr<Texture> createText(const std::string& text);
    virtual void getTextSize(const std::string& text, int* w, int* h);
    virtual void wrapText(const char* text, int maxWidth, char* wrappedText);
    virtual std::shared_ptr<Texture> createBitmapFont(const std::string& font_path,const doengine::Color& bg,const doengine::Color& fg)override;
    virtual int getFontHeight() override;
    virtual Rect getTextSize(const char* str) override;


    std::shared_ptr<Texture> createGlyph();
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
    std::weak_ptr<Application> app;
    bool checkAppIsRunning();
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