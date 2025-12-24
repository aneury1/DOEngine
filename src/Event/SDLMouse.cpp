#include "SDLMouse.h"
#include "DOEngine_SDL_includes.h"

namespace doengine
{
namespace devices
{

SDLMouse::SDLMouse(unsigned int which, unsigned int bMask, Point p)
    : buttonMask(bMask), which(which), position{p}
{
    updateValues();
}

unsigned int SDLMouse::getMouseId() const
{
    return which;
}

bool SDLMouse::isRightClick() const
{
    return (buttonMask & SDL_BUTTON_RMASK) == SDL_BUTTON_RMASK;
}

bool SDLMouse::isLeftClick() const
{
    return (buttonMask & SDL_BUTTON_LMASK) == SDL_BUTTON_LMASK;
}

bool SDLMouse::isMiddleClick() const
{
    return (buttonMask & SDL_BUTTON_MMASK) == SDL_BUTTON_MMASK;
}

void SDLMouse::getPosition(Point& point)
{
    point.x = position.x;
    point.y = position.y;
}

const Point& SDLMouse::getMotionPosition()const
{
    return motion;
}

const Point& SDLMouse::getPosition() const
{
    return position;
}

void SDLMouse::getButtonStateBitset(
    std::bitset<Mouse::BUTTONS_COUNT>& buttonsState) const
{
    buttonsState.set(buttonMask);
}

void SDLMouse::updateValues()
{
    buttonMask = SDL_GetMouseState(&position.x, &position.y);
}

const Point& SDLMouse::getWheelScroll() const
{
    return scroll;
}

void SDLMouse::setScroll(int x, int y)
{
    scroll.x =x;
    scroll.y =y;
}

Rect Mouse::getMousePosition()
{
    Rect rect;
    rect.w = 1;
    rect.h = 1;
    SDL_GetMouseState(&rect.x, &rect.y);
    return rect;
}

uint8_t Mouse::getButtonPressed()
{
    unsigned char ret;
    Rect rect;
    rect.w = 1;
    rect.h = 1;
    auto mouse = SDL_GetMouseState(&rect.x, &rect.y);
    if(mouse&SDL_BUTTON(SDL_BUTTON_LEFT))
        ret |= (uint8_t)Mouse::MouseButtonDown::Left;
    if(mouse&SDL_BUTTON(SDL_BUTTON_RIGHT))
        ret |= (uint8_t)Mouse::MouseButtonDown::Right;
    if(mouse&SDL_BUTTON(SDL_BUTTON_MIDDLE))
        ret |= (uint8_t)Mouse::MouseButtonDown::Center;

    return ret;
}


} // namespace devices
} // namespace doengine