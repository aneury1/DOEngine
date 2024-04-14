#ifndef DOENGINE_SDL_INCLUDES_HPP_DEFINED
#define DOENGINE_SDL_INCLUDES_HPP_DEFINED

#ifdef DOENGINE_TESTING
#include "mocks/SDLMock.h"
#else
extern "C"
{
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_ttf.h>
}
#endif

#endif