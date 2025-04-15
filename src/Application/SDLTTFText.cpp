#include <string>

#include "Application.h"
#include "SDLTTFText.h"

using std::string;

namespace doengine
{

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
void SDLTTFText::DrawText(const char* text, int x, int y)
{
    auto renderer = Application::getApplication()->getRender();
    auto nativeRenderer = (SDL_Renderer*)renderer->getNativeRenderer();
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
    SDL_Surface* sf = TTF_RenderText(font, text, scolor, bg);
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
}

 
void SDLTTFText::wrapText(const char* text, int maxWidth, char* wrappedText) 
{
    const char* current = text;
    const char* wordStart;
    char line[256] = "";
    char temp[256] = "";
    int width = 0;

    while (*current) {
        wordStart = current;

        // Find the end of the current word
        while (*current && *current != ' ' && *current != '\n') {
            current++;
        }

        // Copy the word to a temporary buffer
        strncpy(temp, wordStart, current - wordStart);
        temp[current - wordStart] = '\0';

        // Check the width of the line if the word is added
        char testLine[256];
        snprintf(testLine, sizeof(testLine), "%s %s", line, temp);
        TTF_SizeText(font, testLine, &width, NULL);

        if (width > maxWidth) {
            // Add the current line to the wrapped text
            strcat(wrappedText, line);
            strcat(wrappedText, "\n");

            // Start a new line with the current word
            strcpy(line, temp);
        } else {
            // Add the word to the current line
            if (*line) {
                strcat(line, " ");
            }
            strcat(line, temp);
        }

        // Move to the next word
        if (*current == ' ') {
            current++;
        }
    }

    // Add the last line to the wrapped text
    if (*line) {
        strcat(wrappedText, line);
        strcat(wrappedText, "\n");
    }
}


}; // namespace doengine