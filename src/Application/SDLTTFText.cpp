#include "SDLTTFText.h"
#include "Application.h"
#include "DOEngine_SDL_includes.h"
#include "Logger.h"
#include <map>
#include <string>

using std::string;

namespace doengine
{
static const int CHAR_WIDTH = 16; // Width of each character in the sprite sheet
static const int CHAR_HEIGHT =
    16; // Height of each character in the sprite sheet
static const int CHARS_PER_ROW =
    16; // How many characters are in one row of the sprite sheet
static const int CHARSET_SIZE = 96;
namespace
{
std::map<char, SDL_Rect> charMap;
std::map<int, SDL_Texture*> memoryBitMapFonts;
int current_index = 0;
} // namespace

SDLTTFText::SDLTTFText() : font{nullptr}
{
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
        delete glyphTexture;
}

void SDLTTFText::setColor(Color fg, Color bg)
{
    this->fg_color = fg;
    this->bg_color = bg;
    SDL_SetTextureColorMod(glyph_texture, fg_color.r, fg_color.g, fg_color.b);
    SDL_SetTextureAlphaMod(glyph_texture, fg_color.a);
}
void SDLTTFText::setColor(Color color)
{
    this->fg_color = color;
}

void SDLTTFText::setForegroundColor(Color color)
{
    this->fg_color = color;
    SDL_SetTextureColorMod(glyph_texture, fg_color.r, fg_color.g, fg_color.b);
    SDL_SetTextureAlphaMod(glyph_texture, fg_color.a);
}
void SDLTTFText::setBackgroundColor(Color color)
{
    this->bg_color = color;
}

void SDLTTFText::setFontSize(int fntSize)
{
    if (font)
        TTF_SetFontSize(font, fntSize);
}

void SDLTTFText::setFont(const std::string& path, int fntsize)
{
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

static void drawText(SDL_Renderer* renderer, const std::string& text, int x,
                     int y)
{
    auto fontTexture = memoryBitMapFonts[1];
    for (size_t i = 0; i < text.length(); i++)
    {
        char c = text[i];
        if (charMap.find(c) == charMap.end())
            continue;

        SDL_Rect srcRect = charMap[c];
        SDL_Rect destRect = {x + static_cast<int>(i * CHAR_WIDTH), y,
                             CHAR_WIDTH, CHAR_HEIGHT * 2};

        int result = SDL_RenderCopy(renderer, fontTexture, &srcRect, &destRect);
        /// SDL_Log("TRying....%d %s", result, SDL_GetError());
    }
}

void SDLTTFText::DrawText(const char* text, int x, int y)
{
    auto renderer = Application::getApplication()->getRender();
    auto nativeRenderer = (SDL_Renderer*)renderer->getNativeRenderer();
    /// SDL_Log("Current Index for Drawing=%d", current_index);

    /// drawText(nativeRenderer, std::string(text), x, y);

    /// SDL_Log("----XXXXX");

    /// return;

    if (DrawTextByGlyphs(x, y, text))
        return;
    LogOuput(logger_type::Information, "Default Behavour");
    SDL_Color bg;
    bg.a = bg_color.a;
    bg.r = bg_color.r;
    bg.b = bg_color.b;
    bg.g = bg_color.g;
    SDL_Color scolor;
    scolor.r = fg_color.r;
    scolor.g = fg_color.g;
    scolor.b = fg_color.b;
    scolor.a = fg_color.a;
    SDL_Surface* sf = TTF_RenderText(
        font, text, scolor, toColor<SDL_Color>(doengine::Colors::black));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(nativeRenderer, sf);
    if (texture)
    {
        SDL_Rect offset;
        offset.x = x;
        offset.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &offset.w, &offset.h);
        SDL_RenderCopy(nativeRenderer, texture, NULL, &offset);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(sf);
        texture = nullptr;
        sf = nullptr;
    }
    else
    {
        ///  DO_DEBUG("cANT REDNER FONT???");
    }
}
void SDLTTFText::getTextSize(const std::string& text, int* w, int* h)
{
    if (font)
        TTF_SizeText(font, text.c_str(), w, h);
}

Texture* SDLTTFText::createText(const std::string& text)
{
    return nullptr;
}

void SDLTTFText::wrapText(const char* text, int maxWidth, char* wrappedText)
{
    const char* current = text;
    const char* wordStart;
    char line[255] = "";
    char temp[255] = "";
    int width = 0;

    while (*current)
    {
        wordStart = current;

        // Find the end of the current word
        while (*current && *current != ' ' && *current != '\n')
        {
            current++;
        }

        // Copy the word to a temporary buffer
        strncpy(temp, wordStart, current - wordStart);
        temp[current - wordStart] = '\0';

        // Check the width of the line if the word is added
        char testLine[256];
        snprintf(testLine, sizeof(testLine), "%s %s", line, temp);
        TTF_SizeText(font, testLine, &width, NULL);

        if (width > maxWidth)
        {
            // Add the current line to the wrapped text
            strcat(wrappedText, line);
            strcat(wrappedText, "\n");

            // Start a new line with the current word
            strcpy(line, temp);
        }
        else
        {
            // Add the word to the current line
            if (*line)
            {
                strcat(line, " ");
            }
            strcat(line, temp);
        }

        // Move to the next word
        if (*current == ' ')
        {
            current++;
        }
    }

    // Add the last line to the wrapped text
    if (*line)
    {
        strcat(wrappedText, line);
        strcat(wrappedText, "\n");
    }
}

void replacePixels(SDL_Texture* texture, SDL_Renderer* renderer, int width,
                   int height, SDL_Color newc, SDL_Color bg)
{
    // Allocate memory for pixel data
    Uint32* pixels = new Uint32[width * height];

    // Get the texture format
    Uint32 format;
    SDL_QueryTexture(texture, &format, NULL, NULL, NULL);
    SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);

    // Copy the current pixel data
    SDL_RenderReadPixels(renderer, NULL, format, pixels,
                         width * sizeof(Uint32));

    // Define the yellow color to replace (0xFFFF00 in RGB)
    Uint32 yellow = SDL_MapRGB(mappingFormat, bg.r, bg.g, bg.b);
    Uint32 newColor = SDL_MapRGB(mappingFormat, newc.r, newc.g, newc.b);

    // Modify only yellow pixels
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
}

Texture* SDLTTFText::createBitmapFont(const std::string& font_path,
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
        return nullptr;
    }

    // Load TTF Font
    TTF_Font* font = TTF_OpenFont(font_path.c_str(), CHAR_HEIGHT);
    if (!font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s",
                     TTF_GetError());
        return nullptr;
    }

    // Create texture to store characters
    int textureWidth = CHAR_WIDTH * CHARS_PER_ROW;
    int textureHeight = ((CHARSET_SIZE / CHARS_PER_ROW) + 1) * CHAR_HEIGHT;

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET,
                                             textureWidth, textureHeight);
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Failed to create texture: %s", SDL_GetError());
        TTF_CloseFont(font);
        return nullptr;
    }

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    // SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    // Render each character to the texture
    int x = 0, y = 0;

    for (int i = 32; i < 32 + CHARSET_SIZE; i++)
    { // ASCII printable range
        char c = static_cast<char>(i);

        SDL_Surface* charSurface =
            /// TTF_RenderGlyph_Solid
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
        SDL_Rect dstRect = {x, y, CHAR_WIDTH, CHAR_HEIGHT};

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

        x += CHAR_WIDTH;
        if (x + CHAR_WIDTH > textureWidth)
        {
            x = 0;
            y += CHAR_HEIGHT;
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
    SDL_Color newc;
    newc.r = 0;
    newc.b = 200;
    newc.g = 100;
    newc.a = 100;
    replacePixels(texture, renderer, w, h, newc, yellows);
    // Assign the texture to a Texture object
    current_index = 1;
    memoryBitMapFonts[1] = texture;
    Texture* ret = new Texture();
    return ret->setNativeTexture(texture);
}
constexpr const char* defaultGlyph =
    " !\"#$%&'()*+,-./"
    "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
    "abcdefghijklmnopqrstuvwxyz{|}~";

Texture* SDLTTFText::createGlyph()
{
    auto rrenderer = Application::getApplication()->getRender();
    auto renderer = static_cast<SDL_Renderer*>(rrenderer->getNativeRenderer());
    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer is null!");
        LogOuput(logger_type::Error, "GlyphTexture is Null");
        return nullptr;
    }
    SDL_Color white{255, 255, 255, 255};
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

    glyph_texture = SDL_CreateTextureFromSurface(renderer, atlas);
    SDL_SetTextureBlendMode(glyph_texture, SDL_BLENDMODE_BLEND);

    SDL_FreeSurface(atlas);
    Texture* ret = new Texture();
    if (glyphTexture)
    {
        delete glyphTexture;
        glyphTexture = nullptr;
    }
    LogOuput(logger_type::Error, "GlyphTexture is Created");

    glyphTexture = new Texture();
    glyphTexture->setNativeTexture(glyph_texture);
    return ret->setNativeTexture(glyph_texture);
}

bool SDLTTFText::DrawTextByGlyphs(int x, int y, const std::string& text,
                                  int max_width)
{
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

    // Apply text color

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

        SDL_RenderCopy(renderer, glyph_texture, &src, &dest);
        /// SDL_RenderCopy(renderer, glyph_texture, &g.src, &dst);
        /// glyphTexture->Draw(g.src,dest);
        cursor_x += g.advance;
    }
    return true;
}

int SDLTTFText::getFontHeight()
{
    if (font)
        return TTF_FontHeight(font);
    return 0;
}

doengine::Rect SDLTTFText::getTextSize(const char* str)
{
    doengine::Rect rect;

    return rect;
}

#include <sstream>

BitmapTextRenderer::BitmapTextRenderer()
{
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
    color = color;
    dirty = true;
}

void BitmapTextRenderer::setLineSpacing(int pixels)
{
    lineSpacing = pixels;
    dirty = true;
}

void BitmapTextRenderer::setAlignment(Alignment align)
{
    alignment = align;
    dirty = true;
}

void BitmapTextRenderer::setText(const std::string& text)
{
    this->text = text;
    dirty = true;
}

void BitmapTextRenderer::setConstraints(int maxWidth, int maxHeight)
{
    maxWidth = maxWidth;
    maxHeight = maxHeight;
    dirty = true;
}

void BitmapTextRenderer::nextPage()
{
    if (currentPage + 1 < pages.size())
    {
        currentPage++;
    }
}

void BitmapTextRenderer::prevPage()
{
    if (currentPage > 0)
    {
        currentPage--;
    }
}

void BitmapTextRenderer::setPage(size_t page)
{
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

    while (words >> word)
    {
        std::string test = line.empty() ? word : line + " " + word;
        int w;
        TTF_SizeUTF8(font, test.c_str(), &w, nullptr);

        if (w > maxWidth && !line.empty())
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

    for (const auto& textLine : lines)
    {
        SDL_Surface* surface =
            TTF_RenderUTF8_Blended(font, textLine.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

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
    clearCache();
    if (!font || text.empty())
        return;

    auto lines = wordWrap(text);
    buildPages(lines);
    currentPage = 0;
    dirty = false;
}

}; // namespace doengine