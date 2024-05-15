#pragma once

#include "Keyboard.h"

namespace doengine
{

class SDLKeyboard : public Keyboard
{
  public:
    SDLKeyboard();

    const unsigned char* getKeysBitset() const override;
};

}; // namespace doengine