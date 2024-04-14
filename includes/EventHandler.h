#pragma once

// #include "DOEngine.h"

class KeyDownEvent
{

  public:
    ~KeyDownEvent()
    {
    }

    virtual void OnKeydown(int code) = 0;
};

class KeyUpEvent
{

  public:
    ~KeyUpEvent()
    {
    }

    virtual void OnKeyup(int code) = 0;
};

class JoyButtonDownEvent
{
  public:
    ~JoyButtonDownEvent()
    {
    }

    virtual void OnButtonDown(int button) = 0;
};

class JoyButtonUpEvent
{
  public:
    ~JoyButtonUpEvent()
    {
    }

    virtual void OnButtonUp(int button) = 0;
};

class JoyButtonTriggerEvent
{
  public:
    ~JoyButtonTriggerEvent()
    {
    }

    virtual void OnButtonTriggered(int button, int bias) = 0;
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

enum class MouseButton : unsigned char
{
    Left = 1,
    Middle,
    Right,
    X1,
    X2
};

struct MouseEvent
{

    virtual ~MouseEvent()
    {
    }

    virtual void MouseMove(unsigned int which, int x, int y) = 0;

    virtual void MouseButtonDown(unsigned int which, MouseButton button) = 0;

    virtual void MouseButtonUp(unsigned int which, MouseButton button) = 0;
};