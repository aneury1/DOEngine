#pragma once

#include "Joypad.h"
#include "Keyboard.h"
#include "Mouse.h"

using doengine::devices::Joypad;
using doengine::devices::Keyboard;
using doengine::devices::Mouse;

namespace doengine
{


struct MouseEvent{
   virtual void OnMouseMovement(int x, int y) = 0;
   virtual void OnMouseButtonDown(Uint8 left, Uint8 right, int x, int y) = 0;
   virtual void OnMouseButtonUp(Uint8 left, Uint8 right, int x, int y) = 0;
};


class KeyDownEvent
{
  public:
    ~KeyDownEvent()
    {
    }

    virtual void OnKeydown(const Keyboard&) = 0;
};

class KeyUpEvent
{
  public:
    ~KeyUpEvent()
    {
    }

    virtual void OnKeyup(const Keyboard&) = 0;
};

class JoyButtonDownEvent
{
  public:
    ~JoyButtonDownEvent()
    {
    }

    virtual void OnButtonDown(const Joypad&) = 0;
};

class JoyButtonUpEvent
{
  public:
    ~JoyButtonUpEvent()
    {
    }

    virtual void OnButtonUp(const Joypad&) = 0;
};

class JoyButtonTriggerEvent
{
  public:
    ~JoyButtonTriggerEvent()
    {
    }

    virtual void OnButtonTriggered(const Joypad&) = 0;
};

class MouseMovementEvent
{
  public:
    ~MouseMovementEvent()
    {
    }

    virtual void OnMouseMovement(int x, int y) = 0;
};

class MouseStopEvent
{
  public:
    ~MouseStopEvent()
    {
    }

    virtual void OnMouseMovement(int x, int y) = 0;
};

class TouchEventDown
{
  public:
    ~TouchEventDown()
    {
    }

    virtual void OnTouchDown(int x, int y) = 0;
};

class TouchUpDown
{
  public:
    ~TouchUpDown()
    {
    }

    virtual void OnTouchUp(int x, int y) = 0;
};

class OnMessageQueue
{
  public:
    ~OnMessageQueue()
    {
    }

    virtual void HandleByDescriptor(int fd, void* buffer) = 0;
};

struct MouseEvent
{
    virtual ~MouseEvent()
    {
    }

    virtual void MouseMove(const Mouse&) = 0;
    virtual void MouseButtonDown(const Mouse&) = 0;
    virtual void MouseButtonUp(const Mouse&) = 0;
};

} // namespace doengine