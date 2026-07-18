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

#include "TextField.h"
#include "Color.h"
#include "Geometric.h"
#include "Logger.h"

namespace doengine
{
    Rect rect;
    Color textColor;
    Color bgColor;
    Color borderColor;
    std::string text;
    bool focused;

    std::string fontsrc;
    std::shared_ptr<TTFText> font;
    std::shared_ptr<doengine::Renderer> renderer;
TextField::TextField(int x, int y, int w, int h, const std::string& font)
    : rect{x, y, w, h}, focused(false), fontsrc(font),  renderer(nullptr)
{
    textColor = {255, 0, 0, 255};     // Black text
    bgColor = {255, 255, 255, 255}; // White background
    borderColor = {0, 0, 0, 255};   // Black border
    text = "";
    this->font =std::make_shared<TTFText>();
    this->font->setFont(font, 19);
    this->font->setColor(textColor);
    renderer = Application::getApplication()->getRender();
}

void TextField::MouseMove(const Mouse&  )
{
}
void TextField::MouseButtonDown(const Mouse& mouse)
{
    auto button = mouse.getMousePosition();
    int mx = button.x;
    int my = button.y;
    focused = (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y &&
               my <= rect.y + rect.h);
}
void TextField::MouseButtonUp(const Mouse&)
{
}
   void TextField::MouseWheel(const Mouse&){}
void TextField::OnKeydown(const Keyboard& keyboard)
{
    auto keys = keyboard.getKeysBitset();
    if (keys[SCANCODE_BACKSPACE] && !text.empty())
    {
        text.pop_back();
    }
    if (keys[SCANCODE_RETURN] && onEnterPressed)
    {
        onEnterPressed(getText());
    }
}

void TextField::OnKeyup(const Keyboard&)
{
}
#include "Logger.h"
void TextField::OnTextInput(const std::string& text)
{
    ////LogOuput(logger_type::Info,"HE");
    if (focused)
    {
        this->text += text;
    }
}

void TextField::Render()
{
    LogOuput(logger_type::Information,"TextField::Render");
    // Draw background
    /// SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b,
    /// bgColor.a); SDL_RenderFillRect(renderer, &rect);
    renderer->DrawFillRect(rect, bgColor);
    // Draw border
    /// SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g,
    /// borderColor.b, borderColor.a); SDL_RenderDrawRect(renderer, &rect);
    renderer->DrawRect(rect, borderColor, 1);
    // Draw text
    if (!text.empty())
    {
        // SDL_Surface* textSurface = TTF_RenderText_Blended(font,
        // text.c_str(), textColor); SDL_Texture* textTexture =
        // SDL_CreateTextureFromSurface(renderer, textSurface);

        //int textSurfaceH = 100;
        //int textSurfaceW = 100;

        // Rect textRect = {rect.x + 5, rect.y + (rect.h - textSurfaceH) / 2,
        //                 textSurfaceW, textSurfaceH};
        
        font->setColor(Colors::red);
        font->DrawText(rect.x + 15, rect.y + 14, text.c_str());
        /// SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        /// SDL_FreeSurface(textSurface);
        /// SDL_DestroyTexture(textTexture);
    }
}

void TextField::setOnEnterKeyPressed(std::function<void(const std::string&)> fn)
{
    this->onEnterPressed = fn;
}

std::string TextField::getText() const
{
    return text;
}

} // namespace doengine