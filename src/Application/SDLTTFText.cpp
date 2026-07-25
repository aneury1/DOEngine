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


#include "SDLTTFText.h"
#include "Application.h"
#include "DOEngine_SDL_includes.h"
#include "Logger.h"
#include <map>
#include <string>
#include <cstring>
#include <sstream>

using std::string;

namespace doengine
{
static const int CharWidth = 16; // Width of each character in the sprite sheet
static const int CharHeight =
    16; // Height of each character in the sprite sheet
static const int CharsPerRow =
    16; // How many characters are in one row of the sprite sheet
static const int CharsetSize = 96;
namespace
{
std::map<char, SDL_Rect> charMap;
std::map<int, SDL_Texture*> memoryBitMapFonts;
int current_index = 0;
} // namespace

SDLTTFText::SDLTTFText() : glyph_height{0}, font{nullptr}, glyph_texture{nullptr}
{
    app = doengine::Application::getApplication();
}

bool SDLTTFText::checkAppIsRunning(){
    if(auto locked = app.lock()){
        return locked->IsRunning();
    }
    return false;
}

SDLTTFText::~SDLTTFText()
{
    if (glyph_texture)
        SDL_DestroyTexture(glyph_texture);
    glyph_texture = nullptr;
    if (font)
        TTF_CloseFont(font);
    font = nullptr;
    if (this->glyphTexture)
        glyphTexture.reset();
}

void SDLTTFText::setColor(Color fg, Color bg)
{
    if(!checkAppIsRunning())return;
    this->fg_color = fg;
    this->bg_color = bg;
    SDL_SetTextureColorMod(glyph_texture, fg_color.r, fg_color.g, fg_color.b);
    SDL_SetTextureAlphaMod(glyph_texture, fg_color.a);
}
void SDLTTFText::setColor(Color color)
{
    if(!checkAppIsRunning())return;
    this->fg_color = color;
    // createGlyph() rebuilds the glyph atlas and already updates
    // this->glyph_texture / this->glyphTexture (freeing the previous
    // atlas internally). Nothing further needs to be done here -
    // previously this code destroyed the texture it had just created
    // and then re-pointed glyph_texture at the now-dangling pointer.
    createGlyph();
}

void SDLTTFText::setForegroundColor(Color color)
{
    if(!checkAppIsRunning())return;

    this->fg_color = color;
    SDL_SetTextureColorMod(glyph_texture, fg_color.r, fg_color.g, fg_color.b);
    SDL_SetTextureAlphaMod(glyph_texture, fg_color.a);
}
void SDLTTFText::setBackgroundColor(Color color)
{
    if(!checkAppIsRunning())return;

    this->bg_color = color;
}

void SDLTTFText::setFontSize(int fntSize)
{
    if(!checkAppIsRunning())return;

    if (font)
        TTF_SetFontSize(font, fntSize);
}

void SDLTTFText::setFont(const std::string& path, int fntsize)
{
    if(!checkAppIsRunning())return;

    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }
    LogOuput(logger_type::Information, "FontSRc=%s", path.c_str());
    font = TTF_OpenFont(path.c_str(), fntsize);
    if (font)
    {
        this->path = path;
        this->glyphTexture = createGlyph();
    }
    else
    {
        LogOuput(logger_type::Error, "font could not be opened %s",
                 SDL_GetError());
    }
}

[[maybe_unused]]static void drawText(SDL_Renderer* renderer, const std::string& text, int x,
                     int y)
{
    ////if(!checkAppIsRunning())return;
    if(renderer == nullptr) return;

    auto fontTexture = memoryBitMapFonts[1];
    for (size_t i = 0; i < text.length(); i++)
    {
        char c = text[i];
        if (charMap.find(c) == charMap.end())
            continue;

        SDL_Rect srcRect = charMap[c];
        SDL_Rect destRect = {x + static_cast<int>(i * CharWidth), y,
                             CharWidth, CharHeight * 2};

        SDL_RenderCopy(renderer, fontTexture, &srcRect, &destRect);
        /// SDL_Log("TRying....%d %s", result, SDL_GetError());
    }
}

void SDLTTFText::DrawText(const char* text, int x, int y)
{
    if(!checkAppIsRunning())return;

    auto renderer = Application::getApplication()->getRender();
    auto nativeRenderer = (SDL_Renderer*)renderer->getNativeRenderer();

    if (DrawTextByGlyphs(x, y, text))
        return;
    LogOuput(logger_type::Information, "Default Behavour");

    SDL_Color scolor;
    scolor.r = fg_color.r;
    scolor.g = fg_color.g;
    scolor.b = fg_color.b;
    scolor.a = fg_color.a;
    // NOTE: this fallback path ignores bg_color and always renders against
    // black; setBackgroundColor() currently has no effect on this path.
    SDL_Surface* sf = TTF_RenderText(
        font, text, scolor, toColor<SDL_Color>(doengine::Colors::black));
    if (!sf)
    {
        LogOuput(logger_type::Error, "TTF_RenderText failed: %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(nativeRenderer, sf);
    if (texture)
    {
        SDL_Rect offset;
        offset.x = x;
        offset.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &offset.w, &offset.h);
        SDL_RenderCopy(nativeRenderer, texture, NULL, &offset);

        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    else
    {
        LogOuput(logger_type::Error, "cannot create texture from font surface: %s",
                 SDL_GetError());
    }

    // sf must be freed regardless of whether texture creation succeeded -
    // previously this leaked whenever SDL_CreateTextureFromSurface failed.
    SDL_FreeSurface(sf);
    sf = nullptr;
}
void SDLTTFText::getTextSize(const std::string& text, int* w, int* h)
{
    if (font)
        TTF_SizeText(font, text.c_str(), w, h);
}

std::shared_ptr<Texture> SDLTTFText::createText(const std::string&  )
{
    return nullptr;
}

void SDLTTFText::wrapText(const char* text, int maxWidth, char* wrappedTextOutput)
{
    std::string wrappedText;
    std::string line;
    std::string word;

    std::istringstream stream(text);
    if(!checkAppIsRunning()|| !font)return;

    while (stream >> word)
    {
        std::string testLine = line.empty()
            ? word
            : line + " " + word;

        int width = 0;
        TTF_SizeText(font, testLine.c_str(), &width, nullptr);

        if (width > maxWidth && !line.empty())
        {
            wrappedText += line;
            wrappedText += '\n';

            line = word;
        }
        else
        {
            line = std::move(testLine);
        }
    }

    if (!line.empty())
    {
        wrappedText += line;
    }

    // Copy the result into the caller-provided buffer. NOTE: this API takes
    // no buffer-size parameter, so there is no way to bounds-check safely
    // here - previously the result was computed and silently discarded.
    // Callers must ensure wrappedTextOutput is large enough; consider
    // extending the public API with an explicit buffer-size argument.
    if (wrappedTextOutput)
    {
        std::strcpy(wrappedTextOutput, wrappedText.c_str());
    }
}

void replacePixels(SDL_Texture* texture, SDL_Renderer* renderer, int width,
                   int height, SDL_Color newc, SDL_Color bg)
{
    if(!texture || !renderer )return;
    
    // Reading pixels via SDL_RenderReadPixels reads from whatever texture is
    // currently bound as the render target, NOT the `texture` argument.
    // Previously this function was called after the render target had
    // already been reset to the default target (the window), so it was
    // reading/rewriting the wrong pixels entirely. Bind `texture` as the
    // target for the duration of this call and restore the previous target
    // afterward.
    SDL_Texture* previousTarget = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, texture);

    // Allocate memory for pixel data
    Uint32* pixels = new Uint32[width * height];

    // Get the texture format
    Uint32 format;
    SDL_QueryTexture(texture, &format, NULL, NULL, NULL);
    SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);

    // Copy the current pixel data
    SDL_RenderReadPixels(renderer, NULL, format, pixels,
                         width * sizeof(Uint32));

    // Define the color to replace
    Uint32 yellow = SDL_MapRGB(mappingFormat, bg.r, bg.g, bg.b);
    Uint32 newColor = SDL_MapRGB(mappingFormat, newc.r, newc.g, newc.b);

    // Modify only matching pixels
    for (int i = 0; i < width * height; i++)
    {
        if (pixels[i] == yellow)
        {
            pixels[i] = newColor;
        }
    }

    // Update the texture with modified pixels
    SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));

    // Free allocated resources
    delete[] pixels;
    SDL_FreeFormat(mappingFormat);

    SDL_SetRenderTarget(renderer, previousTarget);
}

std::shared_ptr<Texture> SDLTTFText::createBitmapFont(const std::string& font_path,
                                      const doengine::Color& bg,
                                      const doengine::Color& fg)
{
    int w = 0, h = 0;

    SDL_Log("Starting bitmap font creation...");

    // Get SDL Renderer
    auto rrenderer = Application::getApplication()->getRender();
    auto renderer = static_cast<SDL_Renderer*>(rrenderer->getNativeRenderer());
    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer is null!");
        return std::make_shared<Texture>();
    }

    // Load TTF Font
    TTF_Font* font = TTF_OpenFont(font_path.c_str(), CharHeight);
    if (!font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s",
                     TTF_GetError());
        return std::make_shared<Texture>();
    }

    // Create texture to store characters
    int textureWidth = CharWidth* CharsPerRow;
    int textureHeight = ((CharsetSize / CharsPerRow) + 1) * CharHeight;

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET,
                                             textureWidth, textureHeight);
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Failed to create texture: %s", SDL_GetError());
        TTF_CloseFont(font);
        return std::make_shared<Texture>();
    }

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);

    // Render each character to the texture
    int x = 0, y = 0;

    for (int i = 32; i < 32 + CharsetSize; i++)
    { // ASCII printable range
        char c = static_cast<char>(i);

        SDL_Surface* charSurface =
            TTF_RenderGlyph_Blended(font, c, {fg.r, fg.g, fg.b, fg.a});
        if (!charSurface)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "Failed to render glyph %c: %s", c, TTF_GetError());
            continue;
        }
        SDL_SetColorKey(charSurface, SDL_TRUE,
                        SDL_MapRGB(charSurface->format, 0, 0, 0));
        SDL_Texture* charTexture =
            SDL_CreateTextureFromSurface(renderer, charSurface);
        if (!charTexture)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "Failed to create texture for character %c: %s", c,
                         SDL_GetError());
            SDL_FreeSurface(charSurface);
            continue;
        }

        SDL_Rect srcRect = {0, 0, charSurface->w, charSurface->h};
        SDL_Rect dstRect = {x, y, CharWidth, CharHeight};

        if (SDL_RenderCopy(renderer, charTexture, &srcRect, &dstRect) != 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "SDL_RenderCopy failed for character %c: %s", c,
                         SDL_GetError());
        }
        else
        {
            charMap[c] = dstRect;
        }

        x += CharWidth;
        if (x + CharWidth > textureWidth)
        {
            x = 0;
            y += CharHeight;
        }

        SDL_FreeSurface(charSurface);
        SDL_DestroyTexture(charTexture);
    }

    SDL_SetRenderTarget(renderer, nullptr);
    TTF_CloseFont(font);

    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_Log("Created Bitmap Font Texture [%d, %d]", w, h);

    SDL_Color yellows;
    yellows.r = doengine::Colors::yellow.r;
    yellows.g = doengine::Colors::yellow.g;
    yellows.b = doengine::Colors::yellow.b;
    yellows.a = doengine::Colors::yellow.a;
    // Recolor using the caller-supplied foreground color rather than a
    // hardcoded, unrelated constant - previously this ignored `fg` entirely.
    SDL_Color newc = toColor<SDL_Color>(fg);
    replacePixels(texture, renderer, w, h, newc, yellows);
    // Assign the texture to a Texture object
    current_index = 1;

    // Previously registered textures in memoryBitMapFonts were never
    // destroyed, so re-creating a bitmap font leaked every texture created
    // before it. Free the old entry (if any) before overwriting it.
    auto existing = memoryBitMapFonts.find(1);
    if (existing != memoryBitMapFonts.end() && existing->second)
    {
        SDL_DestroyTexture(existing->second);
    }
    memoryBitMapFonts[1] = texture;

    std::shared_ptr<Texture> ret = std::make_shared<Texture>();
    return ret->setNativeTexture(texture);
}
constexpr const char* defaultGlyph =
    " !\"#$%&'()*+,-./"
    "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
    "abcdefghijklmnopqrstuvwxyz{|}~";

std::shared_ptr<Texture> SDLTTFText::createGlyph()
{
    if(!checkAppIsRunning())return std::make_shared<Texture>();
    auto rrenderer = Application::getApplication()->getRender();
    if(!rrenderer){
        return std::make_shared<Texture>();
    }

    auto renderer = static_cast<SDL_Renderer*>(rrenderer->getNativeRenderer());
    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer is null!");
        LogOuput(logger_type::Error, "GlyphTexture is Null");
        return std::make_shared<Texture>();
    }
    SDL_Color white = {fg_color.r, fg_color.g, fg_color.b, 255};
    glyph_height = TTF_FontHeight(font);

    int atlas_width = 0;

    /* First pass: calculate atlas width */
    for (const char* c = defaultGlyph; *c; ++c)
    {
        int w, h;
        TTF_SizeText(font, std::string(1, *c).c_str(), &w, &h);
        atlas_width += w;
    }

    SDL_Surface* atlas = SDL_CreateRGBSurfaceWithFormat(
        0, atlas_width, glyph_height, 32, SDL_PIXELFORMAT_RGBA32);
    if (!atlas)
    {
        LogOuput(logger_type::Error, "Failed to allocate glyph atlas surface: %s",
                 SDL_GetError());
        return std::make_shared<Texture>();
    }

    SDL_FillRect(atlas, nullptr, SDL_MapRGBA(atlas->format, 0, 0, 0, 0));

    int x_offset = 0;

    /* Second pass: render glyphs */
    for (const char* c = defaultGlyph; *c; ++c)
    {
        char ch = *c;

        SDL_Surface* glyph_surface = TTF_RenderGlyph_Blended(font, ch, white);

        if (!glyph_surface)
            continue;

        Rect dst{x_offset, 0, glyph_surface->w, glyph_surface->h};

        SDL_BlitSurface(glyph_surface, nullptr, atlas,
                        reinterpret_cast<SDL_Rect*>(&dst));

        int minx, maxx, miny, maxy, advance;
        TTF_GlyphMetrics(font, ch, &minx, &maxx, &miny, &maxy, &advance);

        glyphs[ch] = {dst, advance};

        x_offset += glyph_surface->w;
        SDL_FreeSurface(glyph_surface);
    }

    // Free the previous atlas texture before overwriting glyph_texture -
    // previously this leaked the old atlas on every font/color change.
    if (glyph_texture)
    {
        SDL_DestroyTexture(glyph_texture);
        glyph_texture = nullptr;
    }

    glyph_texture = SDL_CreateTextureFromSurface(renderer, atlas);
    if (glyph_texture)
    {
        SDL_SetTextureBlendMode(glyph_texture, SDL_BLENDMODE_BLEND);
    }
    else
    {
        LogOuput(logger_type::Error, "Failed to create glyph atlas texture: %s",
                 SDL_GetError());
    }
    SDL_FreeSurface(atlas);

    glyphTexture.reset();
    glyphTexture = std::make_shared<Texture>();
    glyphTexture->setNativeTexture(glyph_texture);
    return glyphTexture;
}

bool SDLTTFText::DrawTextByGlyphs(int x, int y, const std::string& text,
                                  int max_width)
{
    if(!checkAppIsRunning())return false;
    auto rrenderer = Application::getApplication()->getRender();
    auto renderer = static_cast<SDL_Renderer*>(rrenderer->getNativeRenderer());
    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer is null!");
        LogOuput(logger_type::Error, "GlyphTexture is Null");
        return false;
    }
    if (!glyphTexture)
    {
        LogOuput(logger_type::Error, "GlyphTexture is Null");
        return false;
    }
    int cursor_x = x;
    int cursor_y = y;

    for (char c : text)
    {
        if (c == '\n')
        {
            cursor_x = x;
            cursor_y += glyph_height;
            continue;
        }

        auto it = glyphs.find(c);
        if (it == glyphs.end())
            continue;

        const GlyphInfo& g = it->second;

        if (max_width > 0 && cursor_x + g.src.w > x + max_width)
        {
            cursor_x = x;
            cursor_y += glyph_height;
        }

        SDL_Rect src{
            g.src.x,
            g.src.y,
            g.src.w,
            g.src.h,
        };
        SDL_Rect dest{cursor_x, cursor_y, g.src.w, g.src.h};

        // Only log when the render actually fails - previously this logged
        // an "error" for every single glyph on every frame regardless of
        // success, which is both misleading and a meaningful per-frame cost.
        if (SDL_RenderCopy(renderer, glyph_texture, &src, &dest) != 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "RenderCopy failed: %s",
                         SDL_GetError());
        }

        cursor_x += g.advance;
    }
    return true;
}

int SDLTTFText::getFontHeight()
{
    if(!checkAppIsRunning())return -1;
    if (font)
        return TTF_FontHeight(font);
    return 0;
}

doengine::Rect SDLTTFText::getTextSize(const char*  )
{
    doengine::Rect rect;

    return rect;
}

bool BitmapTextRenderer::checkAppIsRunning(){
    if(app.expired())
      app = Application::getApplication();
    if(auto locked = app.lock()){
        return locked->IsRunning();
    }
    return false;
}


BitmapTextRenderer::BitmapTextRenderer()
{
    if(checkAppIsRunning())
    renderer = (SDL_Renderer*)Application::getApplication()
                   ->getRender()
                   ->getNativeRenderer();
}

BitmapTextRenderer::~BitmapTextRenderer()
{
    
    clearCache();
    if (font)
    {
        TTF_CloseFont(font);
    }
}

bool BitmapTextRenderer::setFont(const std::string& fontPath, int fontSize)
{
    if(!checkAppIsRunning())return false;

    if (font)
    {
        TTF_CloseFont(font);
    }
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    dirty = true;
    return font != nullptr;
}

void BitmapTextRenderer::setColor(SDL_Color color)
{
    if(!checkAppIsRunning())return ;

    // Previously this self-assigned the parameter ("color = color;") and
    // never touched the member, so setColor() had no effect at all.
    this->color = color;
    dirty = true;
}

void BitmapTextRenderer::setLineSpacing(int pixels)
{
    if(!checkAppIsRunning())return ;

    lineSpacing = pixels;
    dirty = true;
}

void BitmapTextRenderer::setAlignment(Alignment align)
{
    if(!checkAppIsRunning())return ;

    alignment = align;
    dirty = true;
}

void BitmapTextRenderer::setText(const std::string& text)
{
    if(!checkAppIsRunning())return ;

    this->text = text;
    dirty = true;
}

void BitmapTextRenderer::setConstraints(int maxWidth, int maxHeight)
{
    if(!checkAppIsRunning())return ;

    // Previously this self-assigned the parameters, so setConstraints() had
    // no effect and word-wrap silently used maxWidth == 0 forever.
    this->maxWidth = maxWidth;
    this->maxHeight = maxHeight;
    dirty = true;
}

void BitmapTextRenderer::nextPage()
{
    if(!checkAppIsRunning())return ;

    if (currentPage + 1 < pages.size())
    {
        currentPage++;
    }
}

void BitmapTextRenderer::prevPage()
{
    if(!checkAppIsRunning())return ;

    if (currentPage > 0)
    {
        currentPage--;
    }
}

void BitmapTextRenderer::setPage(size_t page)
{
    if(!checkAppIsRunning())return ;

    if (page < pages.size())
    {
        currentPage = page;
    }
}

size_t BitmapTextRenderer::getCurrentPage() const
{
    return currentPage;
}

size_t BitmapTextRenderer::getTotalPages() const
{
    return pages.size();
}

void BitmapTextRenderer::render(int x, int y)
{
    if(!checkAppIsRunning()|| !renderer)return ;

    if (dirty)
    {
        rebuild();
    }

    if (pages.empty())
        return;

    int cursorY = y;
    for (const auto& line : pages[currentPage])
    {
        SDL_Rect dst{x, cursorY, line.width, line.height};

        if (alignment != Alignment::Left)
        {
            int offset = maxWidth - line.width;
            if (alignment == Alignment::Center)
                offset /= 2;
            dst.x += offset;
        }

        SDL_RenderCopy(renderer, line.texture, nullptr, &dst);
        cursorY += line.height + lineSpacing;
    }
}

void BitmapTextRenderer::clearCache()
{
    ///if(!checkAppIsRunning()||! line.texture)return ;

    for (auto& page : pages)
    {
        for (auto& line : page)
        {
            SDL_DestroyTexture(line.texture);
        }
    }
    pages.clear();
}

std::vector<std::string> BitmapTextRenderer::wordWrap(const std::string& text)
{
    std::vector<std::string> lines;
    std::istringstream words(text);
    std::string word, line;

    if(!font)return lines;

    while (words >> word)
    {
        std::string test = line.empty() ? word : line + " " + word;
        int w;
        TTF_SizeUTF8(font, test.c_str(), &w, nullptr);

        // maxWidth <= 0 is treated as "no wrapping configured" rather than
        // "wrap after every single word", which was the previous default
        // behavior before setConstraints() actually worked (see fix above).
        if (maxWidth > 0 && w > maxWidth && !line.empty())
        {
            lines.push_back(line);
            line = word;
        }
        else
        {
            line = test;
        }
    }
    if (!line.empty())
        lines.push_back(line);
    return lines;
}

void BitmapTextRenderer::buildPages(const std::vector<std::string>& lines)
{
    std::vector<Line> page;
    int usedHeight = 0;
    if(!font||!renderer) return;

    for (const auto& textLine : lines)
    {
        SDL_Surface* surface =
            TTF_RenderUTF8_Blended(font, textLine.c_str(), color);
        if (!surface)
        {
            LogOuput(logger_type::Error, "TTF_RenderUTF8_Blended failed: %s",
                     TTF_GetError());
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture)
        {
            LogOuput(logger_type::Error, "Failed to create line texture: %s",
                     SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }

        Line line{texture, surface->w, surface->h};
        SDL_FreeSurface(surface);

        if (usedHeight + line.height > maxHeight && !page.empty())
        {
            pages.push_back(page);
            page.clear();
            usedHeight = 0;
        }

        page.push_back(line);
        usedHeight += line.height + lineSpacing;
    }

    if (!page.empty())
    {
        pages.push_back(page);
    }
}

void BitmapTextRenderer::rebuild()
{
    if(!checkAppIsRunning()||!renderer)return ;

    clearCache();
    if (!font || text.empty())
        return;

    auto lines = wordWrap(text);
    buildPages(lines);
    currentPage = 0;
    dirty = false;
}

}; // namespace doengine