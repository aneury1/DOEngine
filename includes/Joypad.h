#pragma once

#include "Color.h"
#include <cstddef>
#include <string>
#include <vector>

namespace doengine::devices
{

enum class PowerLevel : char
{
    Unknown = -1,
    Empty,
    Low,
    Medium,
    Full,
    Wired,
    Max
};

class Joypad
{
  public:
    virtual int getId() const = 0;
    virtual void getName(std::string&) = 0;
    virtual PowerLevel getPowerLevel() const = 0;
    virtual std::size_t getNumberOfButtons() const = 0;
    virtual std::size_t getNumberOfAxes() const = 0;
    virtual int getPlayerIndex() const = 0;

    virtual bool hasLED() const = 0;
    virtual bool hasRumble() const = 0;
    virtual void getJoypadButtonsPressed(std::vector<bool>&) = 0;
    virtual short getAxisValue(int axis) const = 0;

    virtual void startRumble(unsigned short left, unsigned short right,
                             unsigned int duration_ms) = 0;
    virtual void setLEDColor(const Color&) = 0;
    virtual void setPlayerIndex(int index) = 0;
};

} // namespace doengine::devices
