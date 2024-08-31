#pragma once

#include "Mouse.h"

namespace doengine::devices
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
    const Point& getPosition() const override;
    void getButtonStateBitset(
        std::bitset<Mouse::BUTTONS_COUNT>&) const override;

    void updateValues();

  private:
    unsigned int buttonMask;
    unsigned int which;
    Point position;
};
} // namespace doengine::devices
