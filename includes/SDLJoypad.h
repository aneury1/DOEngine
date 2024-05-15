#pragma once

#include "DOEngine_SDL_includes.h"
#include "Joypad.h"

using doengine::devices::Joypad;
using doengine::devices::PowerLevel;

namespace doengine::devices
{
  
const std::string DEFAULT_JOYPAD_NAME = "NOT_FOUND";

class SDLJoypad : public Joypad
{
  public:


    SDLJoypad(SDL_Joystick* joystick);

    virtual int getId() const override;
    virtual void getName(std::string& name) override;
    virtual PowerLevel getPowerLevel() const override;
    virtual std::size_t getNumberOfButtons() const override;
    virtual std::size_t getNumberOfAxes() const override;
    virtual int getPlayerIndex() const override;

    virtual bool hasLED() const override;
    virtual bool hasRumble() const override;
    virtual void getJoypadButtonsPressed(std::vector<bool>&) override;
    virtual short getAxisValue(int axis) const override;

    virtual void startRumble(unsigned short left, unsigned short right,
                             unsigned int duration_ms) override;
    virtual void setLEDColor(const Color&) override;
    virtual void setPlayerIndex(int index) override;

    SDL_Joystick* getNativeJoystick() const;

  private:
    SDL_Joystick* joystick;
    unsigned char index;
};

} // namespace doengine::devices
