#include "SDLKeyboard.h"
#include "DOEngine_SDL_includes.h"

namespace doengine
{
namespace devices
{

SDLKeyboard::SDLKeyboard()
{
}

SDLKeyboard::SDLKeyboard(unsigned char key) : key{key}
{
}

const unsigned char* SDLKeyboard::getKeysBitset() const
{
    return static_cast<const unsigned char*>(SDL_GetKeyboardState(nullptr));
}

const unsigned char SDLKeyboard:: getLastKeyPressed() const
{
    return key;
}

} // namespace devices
} // namespace doengine