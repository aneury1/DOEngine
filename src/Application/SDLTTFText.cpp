#include "SDLTTFText.h"
#include "Application.h"
#include "Logger.h"
#include <SDL2/SDL_ttf.h>
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

void SDLTTFText::setColor(Color fg, Color bg)
{
    this->fg_color = fg;
    this->bg_color = bg;
}
void SDLTTFText::setColor(Color color)
{
    this->fg_color = color;
}

void SDLTTFText::setForegroundColor(Color color)
{
    this->fg_color = color;
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
    font = TTF_OpenFont(path.c_str(), fntsize);
    if (font)
    {
        this->path = path;
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
                             CHAR_WIDTH , CHAR_HEIGHT*2};

        int result = SDL_RenderCopy(renderer, fontTexture, &srcRect, &destRect);
        /// SDL_Log("TRying....%d %s", result, SDL_GetError());
    }
}

void SDLTTFText::DrawText(const char* text, int x, int y)
{
    auto renderer = Application::getApplication()->getRender();
    auto nativeRenderer = (SDL_Renderer*)renderer->getNativeRenderer();
    SDL_Log("Current Index for Drawing=%d", current_index);

    drawText(nativeRenderer, std::string(text), x, y);

    SDL_Log("----XXXXX");

    return;

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
    SDL_Surface* sf =
        TTF_RenderText(font, text, scolor, toColor<SDL_Color>(black));
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
    char line[256] = "";
    char temp[256] = "";
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


void replacePixels(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height, SDL_Color newc, SDL_Color bg) {
    // Allocate memory for pixel data
    Uint32* pixels = new Uint32[width * height];

    // Get the texture format
    Uint32 format;
    SDL_QueryTexture(texture, &format, NULL, NULL, NULL);
    SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);

    // Copy the current pixel data
    SDL_RenderReadPixels(renderer, NULL, format, pixels, width * sizeof(Uint32));

    // Define the yellow color to replace (0xFFFF00 in RGB)
    Uint32 yellow = SDL_MapRGB(mappingFormat, bg.r, bg.g, bg.b);
    Uint32 newColor = SDL_MapRGB(mappingFormat, newc.r, newc.g, newc.b);

    // Modify only yellow pixels
    for (int i = 0; i < width * height; i++) {
        if (pixels[i] == yellow) {
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
            ///TTF_RenderGlyph_Solid
            TTF_RenderGlyph_Blended
            (font, c, {fg.r, fg.g, fg.b, fg.a});
        if (!charSurface)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "Failed to render glyph %c: %s", c, TTF_GetError());
            continue;
        }
            SDL_SetColorKey(charSurface, SDL_TRUE,
                            SDL_MapRGB(charSurface->format, 0,
                                       0,
                                       0));
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
    yellows.r = yellow.r;
    yellows.g = yellow.g;
    yellows.b = yellow.b;
    yellows.a = yellow.a;
    SDL_Color newc;
    newc.r = 0;
    newc.b = 200;
    newc.g = 100;
    newc.a = 100;
    replacePixels(texture,renderer, w,h, newc, yellows);
    // Assign the texture to a Texture object
    current_index = 1;
    memoryBitMapFonts[1] = texture;
    Texture* ret = new Texture();
    return ret->setNativeTexture(texture);
}

}; // namespace doengine