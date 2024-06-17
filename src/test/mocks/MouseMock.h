#pragma once

#include "Mouse.h"
#include <gmock/gmock-function-mocker.h>

using doengine::devices::Mouse;

namespace doengine::mocks
{

class MouseMock : public Mouse
{
  public:
    MOCK_METHOD(unsigned int, getMouseId, (), (const, override));
    MOCK_METHOD(bool, isRightClick, (), (const, override));
    MOCK_METHOD(bool, isLeftClick, (), (const, override));
    MOCK_METHOD(bool, isMiddleClick, (), (const, override));
    MOCK_METHOD(void, getPosition, (Point&), (override));
    MOCK_METHOD(void, getButtonStateBitset, (std::bitset<BUTTONS_COUNT>&),
                (const, override));
};
} // namespace doengine::mocks
