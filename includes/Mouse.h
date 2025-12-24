#pragma once

#include <bitset>
#include <cstddef>

#include "v2d_vector.h"
#include <Geometric.h>

namespace doengine
{
namespace devices
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
    virtual const Point& getPosition() const = 0;
    virtual const Point& getMotionPosition() const = 0;
    virtual void getButtonStateBitset(std::bitset<BUTTONS_COUNT>&) const = 0;
    virtual const Point& getWheelScroll() const = 0;
    enum  MouseButtonDown : uint8_t{
      Left = 1,
      Right = 2,
      Center = 4
    };
    static Rect getMousePosition();
    static uint8_t getButtonPressed();
};

} // namespace devices
} // namespace doengine