#pragma once

#include "Keyboard.h"

namespace doengine
{
namespace devices
{
class SDLKeyboard : public Keyboard
{
    unsigned char key;

  public:
    SDLKeyboard();
    SDLKeyboard(unsigned char key);

    const unsigned char* getKeysBitset() const override;
    virtual const unsigned char getLastKeyPressed() const override;
};
} // namespace devices
} // namespace doengine