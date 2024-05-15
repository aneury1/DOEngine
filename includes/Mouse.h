#pragma once

#include "Geometric.h"
#include "v2d_vector.h"
#include <bitset>
#include <cstddef>

namespace doengine
{

enum class MouseButton : unsigned char
{
    Left = 1,
    Middle,
    Right,
    X1,
    X2
};

class Mouse
{
  public:
    static const size_t BUTTONS_COUNT = 6u;
    virtual unsigned int getMouseId() const = 0;
    virtual bool isRightClick() const = 0;
    virtual bool isLeftClick() const = 0;
    virtual bool isMiddleClick() const = 0;
    virtual void getPosition(Point&) = 0;
    virtual void getButtonStateBitset(std::bitset<BUTTONS_COUNT>&) const = 0;
};

}; // namespace doengine