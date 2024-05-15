#pragma once

#include "Keyboard.h"


class SDLKeyboard : public Keyboard
{
  public:
    SDLKeyboard();

    const unsigned char* getKeysBitset() const override;
};
