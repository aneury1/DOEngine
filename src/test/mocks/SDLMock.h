#pragma once

#include "DOEngine_SDL_includes.h"


namespace doengine
{
namespace mocks
{

class SDLMock
{
  public:
    MOCK_METHOD(Uint32, SDL_GetTicks, ());
    MOCK_METHOD(void, SDL_Delay, (Uint32));
    MOCK_METHOD(void, SDL_Log, (const char*));
    MOCK_METHOD(int, SDL_PollEvent, (SDL_Event*));
    MOCK_METHOD(Uint32, SDL_GetMouseState, (int*, int*));
    MOCK_METHOD(const Uint8*, SDL_GetKeyboardState, (int*));
    MOCK_METHOD(SDL_JoystickID, SDL_JoystickGetDeviceInstanceID, (int));
    MOCK_METHOD(SDL_JoystickID, SDL_JoystickInstanceID, (SDL_Joystick*));
    MOCK_METHOD(SDL_bool, SDL_JoystickHasLED, (SDL_Joystick*));
    MOCK_METHOD(SDL_bool, SDL_JoystickHasRumble, (SDL_Joystick*));
    MOCK_METHOD(int, SDL_JoystickGetPlayerIndex, (SDL_Joystick*));
    MOCK_METHOD(Sint16, SDL_JoystickGetAxis, (SDL_Joystick*, int));
    MOCK_METHOD(Uint8, SDL_JoystickGetButton, (SDL_Joystick*, int));
    MOCK_METHOD(int, SDL_JoystickNumAxes, (SDL_Joystick*));
    MOCK_METHOD(int, SDL_JoystickNumButtons, (SDL_Joystick*));
    MOCK_METHOD(SDL_JoystickPowerLevel, SDL_JoystickCurrentPowerLevel,
                (SDL_Joystick*));
    MOCK_METHOD(int, SDL_JoystickRumble,
                (SDL_Joystick*, Uint16, Uint16, Uint32));
    MOCK_METHOD(void, SDL_JoystickSetPlayerIndex, (SDL_Joystick*, int));
    MOCK_METHOD(int, SDL_JoystickSetLED, (SDL_Joystick*, Uint8, Uint8, Uint8));
    MOCK_METHOD(const char*, SDL_JoystickNameForIndex, (int device_index));
    MOCK_METHOD(const char*, SDL_JoystickName, (SDL_Joystick*));
    MOCK_METHOD(SDL_Joystick*, SDL_JoystickOpen, (int device_index));
    MOCK_METHOD(void, SDL_JoystickClose, (SDL_Joystick * joystick));
    MOCK_METHOD(const char*, SDL_GetError, ());
};

} // namespace mocks
} // namespace doengine

extern doengine::mocks::SDLMock* sdlMock;
void SetSDLMock(doengine::mocks::SDLMock* newSdlMock);

