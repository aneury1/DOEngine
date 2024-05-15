#include "SDLKeyboard.h"
#include "DOEngine_SDL_includes.h"


SDLKeyboard::SDLKeyboard()
{
}

const unsigned char* SDLKeyboard::getKeysBitset() const
{
    return static_cast<const unsigned char*>(SDL_GetKeyboardState(nullptr));
}

