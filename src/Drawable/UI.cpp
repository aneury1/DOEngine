#include "UI.h"
#include "Mouse.h"
#include "Application.h"

///Todo refactor...
#include <SDL2/SDL.h>

namespace doengine
{

MouseBtn ToMouseBtn(Uint8 sdlButton)
{
    switch (sdlButton)
    {
        case SDL_BUTTON_LEFT:   return MouseBtn::Left;
        case SDL_BUTTON_RIGHT:  return MouseBtn::Right;
        case SDL_BUTTON_MIDDLE: return MouseBtn::Middle;
        default:                return MouseBtn::None;
    }
}

BorderPress GetBorderPressState(
    const SDL_Rect& r,
    int             thickness = 2
)
{
    BorderPress result{};
    result.pressed = false;
    result.border  = Border::None;
    result.button  = MouseBtn::None;

    int mx, my;
    Uint32 buttons = SDL_GetMouseState(&mx, &my);

    // No button pressed at all
    if (buttons == 0)
        return result;

    // Inside rectangle?
    if (mx < r.x || mx > r.x + r.w ||
        my < r.y || my > r.y + r.h)
        return result;

    bool left   = mx >= r.x && mx <= r.x + thickness;
    bool right  = mx >= r.x + r.w - thickness && mx <= r.x + r.w;
    bool top    = my >= r.y && my <= r.y + thickness;
    bool bottom = my >= r.y + r.h - thickness && my <= r.y + r.h;

    // Optional: exclude corners
    if ((left || right) && (top || bottom))
        return result;

    if (left)        result.border = Border::Left;
    else if (right)  result.border = Border::Right;
    else if (top)    result.border = Border::Top;
    else if (bottom) result.border = Border::Bottom;
    else             return result;

    // Detect which button is pressed
    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
        result.button = MouseBtn::Left;
    else if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
        result.button = MouseBtn::Right;
    else if (buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE))
        result.button = MouseBtn::Middle;
    else
        return result;

    result.pressed = true;
    result.x = mx;
    result.y = my;

    return result;
}


UIPanel::UIPanel()
{
    backgroundColor.r = 0x43;
    backgroundColor.g = 0x43;
    backgroundColor.b = 0x43;
    backgroundColor.a = 255;
    this->size.w = 200;
    this->size.h = 200;
    renderer = Application::getApplication()->getRender();
}

UIPanel::~UIPanel()
{

}

void UIPanel::Draw()
{
    renderer->DrawFillRect(size, backgroundColor);
    if(mouseOverPanelBorder){
        getRenderer()->DrawFillRect(size, doengine::Colors::yellow1);
        getRenderer()->DrawRect(size, doengine::Colors::red);
    }
}

void UIPanel::Update()
{
    mouseOverPanelBorder = false;
    auto mouse = doengine::devices::Mouse::getMousePosition();
       
}

}