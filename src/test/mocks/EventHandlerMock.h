#pragma once

#include "EventHandler.h"
#include <gmock/gmock-function-mocker.h>


class KeyDownEventMock : public KeyDownEvent
{
  public:
    MOCK_METHOD(void, OnKeydown, (const Keyboard&), (override));
};

class KeyUpEventMock : public KeyUpEvent
{
  public:
    MOCK_METHOD(void, OnKeyup, (const Keyboard&), (override));
};

class JoyButtonUpEventMock : public JoyButtonUpEvent
{
  public:
    MOCK_METHOD(void, OnButtonUp, (const Joypad&), (override));
};

class JoyButtonDownEventMock : public JoyButtonDownEvent
{
  public:
    MOCK_METHOD(void, OnButtonDown, (const Joypad&), (override));
};

class JoyButtonTriggerEventMock : public JoyButtonTriggerEvent
{
  public:
    MOCK_METHOD(void, OnButtonTriggered, (const Joypad&), (override));
};

class MouseMovementEventMock : public MouseMovementEvent
{
  public:
    MOCK_METHOD(void, OnMouseMovement, (int, int), (override));
};

class MouseStopEventMock : public MouseStopEvent
{
  public:
    MOCK_METHOD(void, OnMouseMovement, (int, int), (override));
};

class TouchEventDownMock : public TouchEventDown
{
  public:
    MOCK_METHOD(void, OnTouchDown, (int, int), (override));
};

class TouchUpDownMock : public TouchUpDown
{
  public:
    MOCK_METHOD(void, OnTouchUp, (int, int), (override));
};

class OnMessageQueueMock : public OnMessageQueue
{
  public:
    MOCK_METHOD(void, HandleByDescriptor, (int, void*), (override));
};

struct MouseEventMock : public MouseEvent
{
  public:
    MOCK_METHOD(void, MouseMove, (const Mouse&), (override));
    MOCK_METHOD(void, MouseButtonDown, (const Mouse&), (override));
    MOCK_METHOD(void, MouseButtonUp, (const Mouse&), (override));
};
