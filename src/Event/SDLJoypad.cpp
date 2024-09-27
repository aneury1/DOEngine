#include "SDLJoypad.h"
#include <cstddef>

namespace doengine::devices
{

const std::string SDLJoypad::DEFAULT_JOYPAD_NAME = "NOT_FOUND";

SDLJoypad::SDLJoypad(SDL_Joystick* joystick) : joystick(joystick), index(255)
{
}

int SDLJoypad::getId() const
{
    return static_cast<int>(SDL_JoystickInstanceID(joystick));
}

void SDLJoypad::getName(std::string& name)
{
    const char* strName = SDL_JoystickName(joystick);
    if (strName != nullptr)
    {
        name = strName;
    }
    else
    {
        name = DEFAULT_JOYPAD_NAME;
    }
}

PowerLevel SDLJoypad::getPowerLevel() const
{
    SDL_JoystickPowerLevel powerLevel = SDL_JoystickCurrentPowerLevel(joystick);

    return static_cast<PowerLevel>(powerLevel);
}

std::size_t SDLJoypad::getNumberOfButtons() const
{
    return SDL_JoystickNumButtons(joystick);
}

std::size_t SDLJoypad::getNumberOfAxes() const
{
    return SDL_JoystickNumAxes(joystick);
}

int SDLJoypad::getPlayerIndex() const
{
    return SDL_JoystickGetPlayerIndex(joystick);
}

bool SDLJoypad::hasLED() const
{
    return static_cast<bool>(SDL_JoystickHasLED(joystick));
}

bool SDLJoypad::hasRumble() const
{
    return static_cast<bool>(SDL_JoystickHasRumble(joystick));
}

void SDLJoypad::getJoypadButtonsPressed(std::vector<bool>& buttonsPressed)
{
    buttonsPressed.clear();
    const int btns = getNumberOfButtons();
    for (int i = 0; i < btns; i++)
    {
        buttonsPressed.push_back(SDL_JoystickGetButton(joystick, i));
    }
}

short SDLJoypad::getAxisValue(int axis) const
{
    return SDL_JoystickGetAxis(joystick, axis);
}

void SDLJoypad::startRumble(unsigned short left, unsigned short right,
                            unsigned int duration_ms)
{
    if (hasRumble())
    {
        SDL_JoystickRumble(joystick, left, right, duration_ms);
    }
}

void SDLJoypad::setLEDColor(const Color& color)
{
    if (hasLED())
    {
        SDL_JoystickSetLED(joystick, color.r, color.g, color.b);
    }
}

void SDLJoypad::setPlayerIndex(int index)
{
    SDL_JoystickSetPlayerIndex(joystick, index);
    this->index = index;
}

SDL_Joystick* SDLJoypad::getNativeJoystick() const
{
    return joystick;
}

} // namespace doengine
