#pragma once

#include "abstract/devices/Joypad.h"
#include <gmock/gmock-function-mocker.h>

using doengine::devices::Joypad;
using doengine::devices::PowerLevel;

namespace doengine::mocks
{

class JoypadMock : public Joypad
{
  public:
    MOCK_METHOD(int, getId, (), (const, override));
    MOCK_METHOD(void, getName, (std::string&), (override));
    MOCK_METHOD(PowerLevel, getPowerLevel, (), (const, override));
    MOCK_METHOD(std::size_t, getNumberOfButtons, (), (const, override));
    MOCK_METHOD(std::size_t, getNumberOfAxes, (), (const, override));
    MOCK_METHOD(int, getPlayerIndex, (), (const, override));

    MOCK_METHOD(bool, hasLED, (), (const, override));
    MOCK_METHOD(bool, hasRumble, (), (const, override));
    MOCK_METHOD(void, getJoypadButtonsPressed, (std::vector<bool>&),
                (override));
    MOCK_METHOD(short, getAxisValue, (int), (const, override));

    MOCK_METHOD(void, startRumble,
                (unsigned short, unsigned short, unsigned int), (override));
    MOCK_METHOD(void, setLEDColor, (const Color&), (override));
    MOCK_METHOD(void, setPlayerIndex, (int), (override));
};

} // namespace doengine::mocks
