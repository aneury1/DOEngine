#include "SDLMock.h"
#include <cstddef>

SDLMock* sdlMock = nullptr;

Uint32 SDL_GetTicks()
{
    return sdlMock->SDL_GetTicks();
}

void SDL_Delay(Uint32 a)
{
    sdlMock->SDL_Delay(a);
}

void SDL_Log(const char* fmt, ...)
{
    sdlMock->SDL_Log(nullptr);
}

int SDL_PollEvent(SDL_Event* event)
{
    return sdlMock->SDL_PollEvent(event);
}

Uint32 SDL_GetMouseState(int* x, int* y)
{
    return sdlMock->SDL_GetMouseState(x, y);
}

const Uint8* SDL_GetKeyboardState(int* numkeys)
{
    return sdlMock->SDL_GetKeyboardState(numkeys);
}

SDL_JoystickID SDL_JoystickGetDeviceInstanceID(int index)
{
    return sdlMock->SDL_JoystickGetDeviceInstanceID(index);
}

SDL_JoystickID SDL_JoystickInstanceID(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickInstanceID(joystick);
}

SDL_bool SDL_JoystickHasLED(SDL_Joystick* Joystick)
{
    return sdlMock->SDL_JoystickHasLED(Joystick);
}

SDL_bool SDL_JoystickHasRumble(SDL_Joystick* Joystick)
{
    return sdlMock->SDL_JoystickHasRumble(Joystick);
}

int SDL_JoystickGetPlayerIndex(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickGetPlayerIndex(joystick);
}

Sint16 SDL_JoystickGetAxis(SDL_Joystick* joystick, int axis)
{
    return sdlMock->SDL_JoystickGetAxis(joystick, axis);
}

Uint8 SDL_JoystickGetButton(SDL_Joystick* joystick, int button)
{
    return sdlMock->SDL_JoystickGetButton(joystick, button);
}

int SDL_JoystickNumAxes(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickNumAxes(joystick);
}

int SDL_JoystickNumButtons(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickNumButtons(joystick);
}

SDL_JoystickPowerLevel SDL_JoystickCurrentPowerLevel(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickCurrentPowerLevel(joystick);
}

int SDL_JoystickRumble(SDL_Joystick* joystick, Uint16 left, Uint16 right,
                       Uint32 duration_ms)
{
    return sdlMock->SDL_JoystickRumble(joystick, left, right, duration_ms);
}

void SDL_JoystickSetPlayerIndex(SDL_Joystick* joystick, int player_index)
{
    sdlMock->SDL_JoystickSetPlayerIndex(joystick, player_index);
}

int SDL_JoystickSetLED(SDL_Joystick* joystick, Uint8 red, Uint8 green,
                       Uint8 blue)
{
    return sdlMock->SDL_JoystickSetLED(joystick, red, green, blue);
}

const char* SDL_JoystickNameForIndex(int device_index)
{
    return sdlMock->SDL_JoystickNameForIndex(device_index);
}

const char* SDL_JoystickName(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickName(joystick);
}

SDL_Joystick* SDL_JoystickOpen(int device_index)
{
    return sdlMock->SDL_JoystickOpen(device_index);
}

void SDL_JoystickClose(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickClose(joystick);
}

const char* SDL_GetError(void)
{
    return sdlMock->SDL_GetError();
}

void SetSDLMock(SDLMock* newSdlMock)
{
    sdlMock = newSdlMock;
}

