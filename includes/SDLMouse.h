#pragma once

#include "Mouse.h"

namespace doengine
{
namespace devices
{
class SDLMouse : public Mouse
{
  public:
    SDLMouse(unsigned int which, unsigned int buttonMask, Point p);
    unsigned int getMouseId() const override;
    bool isRightClick() const override;
    bool isLeftClick() const override;
    bool isMiddleClick() const override;
    void getPosition(Point&) override;
    const Point& getMotionPosition() const override;
    const Point& getPosition() const override;
    void getButtonStateBitset(
        std::bitset<Mouse::BUTTONS_COUNT>&) const override;
    virtual const Point& getWheelScroll() const override;
    void updateValues();
    void setScroll(int x, int y);
    Point motion;
  private:
    unsigned int buttonMask;
    unsigned int which;
    Point position;
    
    Point scroll;
};
} // namespace devices
} // namespace doengine