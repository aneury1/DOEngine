#pragma once

#include "EventHandler.h"
#include <gmock/gmock-function-mocker.h>

namespace doengine::mocks
{

class KeyDownEventMock : public KeyDownEvent
{
    MOCK_METHOD(void, OnKeydown, (int), (override));
};

class KeyUpEventMock : public KeyUpEvent
{
    MOCK_METHOD(void, OnKeyup, (int), (override));
};

class JoyButtonUpEventMock : public JoyButtonUpEvent
{
    MOCK_METHOD(void, OnButtonUp, (int), (override));
};

class JoyButtonDownEventMock : public JoyButtonDownEvent
{
    MOCK_METHOD(void, OnButtonDown, (int), (override));
};

class JoyButtonTriggerEventMock : public JoyButtonTriggerEvent
{
    MOCK_METHOD(void, OnButtonTriggered, (int, int), (override));
};

class MouseMovementEventMock : public MouseMovementEvent
{
    MOCK_METHOD(void, OnMouseMovement, (int, int), (override));
};

class MouseStopEventMock : public MouseStopEvent
{
    MOCK_METHOD(void, OnMouseMovement, (int, int), (override));
};

class TouchEventDownMock : public TouchEventDown
{
    MOCK_METHOD(void, OnTouchDown, (int, int), (override));
};

class TouchUpDownMock : public TouchUpDown
{
    MOCK_METHOD(void, OnTouchUp, (int, int), (override));
};

class OnMessageQueueMock : public OnMessageQueue
{
    MOCK_METHOD(void, HandleByDescriptor, (int, void*), (override));
};

struct MouseEventMock : public MouseEvent
{
    MOCK_METHOD(void, MouseMove, (unsigned int, int, int), (override));
    MOCK_METHOD(void, MouseButtonDown, (unsigned int, MouseButton), (override));
    MOCK_METHOD(void, MouseButtonUp, (unsigned int, MouseButton), (override));
};

} // namespace doengine::mocks