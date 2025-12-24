
#include "TextField.h"
#include "Color.h"
#include "Geometric.h"
#include "Logger.h"

namespace doengine
{

TextField::TextField(int x, int y, int w, int h, const std::string& font)
    : rect{x, y, w, h}, fontsrc(font), renderer(renderer), focused(false)
{
    textColor = {0, 0, 0, 255};     // Black text
    bgColor = {255, 255, 255, 255}; // White background
    borderColor = {0, 0, 0, 255};   // Black border
    text = "";
    this->font = new TTFText();
    this->font->setFont(font, 19);
    renderer = Application::getApplication()->getRender();
}

void TextField::MouseMove(const Mouse& mouse)
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
    if (focused) {
        this->text += text;
    }
}

void TextField::render()
{
    // Draw background
    /// SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b,
    /// bgColor.a); SDL_RenderFillRect(renderer, &rect);
    renderer->DrawFillRect(rect, bgColor);
    // Draw border
    /// SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g,
    /// borderColor.b, borderColor.a); SDL_RenderDrawRect(renderer, &rect);
    renderer->DrawRect(rect, doengine::Colors::red, 15);
    // Draw text
    if (!text.empty())
    {
        // SDL_Surface* textSurface = TTF_RenderText_Blended(font,
        // text.c_str(), textColor); SDL_Texture* textTexture =
        // SDL_CreateTextureFromSurface(renderer, textSurface);

        int textSurfaceH = 100;
        int textSurfaceW = 100;

        Rect textRect = {rect.x + 5, rect.y + (rect.h - textSurfaceH) / 2,
                         textSurfaceW, textSurfaceH};
        
        font->DrawText(rect.x+15, rect.y+14, text.c_str());
        /// SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        /// SDL_FreeSurface(textSurface);
        /// SDL_DestroyTexture(textTexture);
    }
}

void TextField::setOnEnterKeyPressed( std::function<void(const std::string&)> fn)
{
    this->onEnterPressed = fn;
}

std::string TextField::getText() const
{
    return text;
}

} // namespace doengine