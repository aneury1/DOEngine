#ifndef DOENGINE_SDL_INCLUDES_HPP_DEFINED
#define DOENGINE_SDL_INCLUDES_HPP_DEFINED

#define FETCHED_CONTENT 1
#warning "Using fetched content"

#ifndef FETCHED_CONTENT
#include "gmock/gmock.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glext.h>
#else
 
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_joystick.h>
#include <SDL_log.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>
#endif

#endif
