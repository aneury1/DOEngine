#include "SDLMouse.h"
#include "DOEngine_SDL_includes.h"



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

void SDLMouse::getButtonStateBitset(
    std::bitset<Mouse::BUTTONS_COUNT>& buttonsState) const
{
    buttonsState.set(buttonMask);
}

void SDLMouse::updateValues()
{
    buttonMask = SDL_GetMouseState(&position.x, &position.y);
}
