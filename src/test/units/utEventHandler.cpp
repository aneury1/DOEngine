#include "Event.h"
#include "abstract/EventHandler.h"
#include "abstract/devices/Mouse.h"
#include "fixtures/DoEngineFixture.h"
#include "mocks/EventHandlerMock.h"
#include "mocks/JoypadMock.h"
#include "mocks/MouseMock.h"
#include "mocks/SDLMock.h"
#include "gmock/gmock.h"
#include <bitset>
#include <cstddef>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tuple>
#include <vector>



class utEventHandler : public DoEngineFixture
{
  public:
    utEventHandler()
        : DoEngineFixture(), _mouseEventMock(), _keyUpEventMock(),
          _keyDownEventMock(), _joyButtonDownMock(), _joyButtonUpMock(),
          _joyButtonTriggerMock()
    {
    }

    void SetUp() override
    {
        DoEngineFixture::SetUp();
        ON_CALL(_sdlMock, SDL_PollEvent(_)).WillByDefault(Return(0));
        ON_CALL(_sdlMock, SDL_JoystickOpen(_)).WillByDefault(Return(nullptr));
        ON_CALL(_sdlMock, SDL_GetError()).WillByDefault(Return("Error"));
        _sut.AddMouseEvent(&_mouseEventMock);
        _sut.AddKeyPressEventListener(&_keyUpEventMock);
        _sut.AddKeyPressEventListener(&_keyDownEventMock);
        _sut.AddJoypadEventListener(&_joyButtonUpMock);
        _sut.AddJoypadEventListener(&_joyButtonDownMock);
        _sut.AddJoypadEventListener(&_joyButtonTriggerMock);
    }

    void TearDown() override
    {
        _sut.RemovedMouseEvent(&_mouseEventMock);
        _sut.RemoveKeyPressEventListener(&_keyUpEventMock);
        _sut.RemoveKeyPressEventListener(&_keyDownEventMock);
        _sut.RemoveJoypadEventListener(&_joyButtonUpMock);
        _sut.RemoveJoypadEventListener(&_joyButtonDownMock);
        _sut.RemoveJoypadEventListener(&_joyButtonTriggerMock);
    }

    void performMoveMouse(SDL_Event& event, const unsigned int which)
    {
        event.type = SDL_MOUSEMOTION;
        event.motion.which = which;
    }

    void performMoveClick(SDL_Event& event, const unsigned int type,
                          const unsigned int which, const unsigned char button)
    {
        event.type = type;
        event.button.button = button;
        event.button.which = which;
    }

    void performKeyPress(SDL_Event& event, const unsigned int type,
                         const unsigned short key, const unsigned char state,
                         const unsigned short mod = KMOD_NONE)
    {
        event.key.type = type;
        event.key.keysym.sym = key;
        event.key.keysym.mod = mod;
        event.key.state = state;
    }

    Event _sut;
    NiceMock<mocks::MouseEventMock> _mouseEventMock;
    NiceMock<mocks::KeyDownEventMock> _keyDownEventMock;
    NiceMock<mocks::KeyUpEventMock> _keyUpEventMock;
    NiceMock<mocks::JoyButtonDownEventMock> _joyButtonDownMock;
    NiceMock<mocks::JoyButtonUpEventMock> _joyButtonUpMock;
    NiceMock<mocks::JoyButtonTriggerEventMock> _joyButtonTriggerMock;
};

TEST_F(utEventHandler, addKeyMouseListener)
{
    NiceMock<mocks::MouseEventMock> mouseEventMock;
    _sut.AddMouseEvent(&mouseEventMock);
    EXPECT_EQ(_sut.mouseEvent.back(), &mouseEventMock);
    _sut.RemovedMouseEvent(&mouseEventMock);

    EXPECT_FALSE(_sut.mouseEvent.size() <= 0);
    EXPECT_NE(_sut.mouseEvent.back(), &mouseEventMock);
}

TEST_F(utEventHandler, addKeyPressListener)
{
    NiceMock<mocks::KeyDownEventMock> keyDownEventMock;
    NiceMock<mocks::KeyUpEventMock> keyUpEventMock;

    _sut.AddKeyPressEventListener(&keyUpEventMock);
    EXPECT_EQ(_sut.keyup.back(), &keyUpEventMock);
    _sut.RemoveKeyPressEventListener(&keyUpEventMock);

    EXPECT_FALSE(_sut.keyup.size() <= 0);
    EXPECT_NE(_sut.keyup.back(), &keyUpEventMock);

    _sut.AddKeyPressEventListener(&keyDownEventMock);
    EXPECT_EQ(_sut.keydown.back(), &keyDownEventMock);
    _sut.RemoveKeyPressEventListener(&keyDownEventMock);

    EXPECT_FALSE(_sut.keydown.size() <= 0);
    EXPECT_NE(_sut.keydown.back(), &keyDownEventMock);
}

TEST_F(utEventHandler, addJoypadListener)
{
    NiceMock<mocks::JoyButtonUpEventMock> joypadBtnUpEvent;
    NiceMock<mocks::JoyButtonDownEventMock> joypadBtnDownEvent;
    NiceMock<mocks::JoyButtonTriggerEventMock> joypadBtnTriggerEvent;

    _sut.AddJoypadEventListener(&joypadBtnUpEvent);
    EXPECT_EQ(_sut.joyButtonUpList.back(), &joypadBtnUpEvent);
    _sut.RemoveJoypadEventListener(&joypadBtnUpEvent);

    EXPECT_FALSE(_sut.joyButtonUpList.size() <= 0);
    EXPECT_NE(_sut.joyButtonUpList.back(), &joypadBtnUpEvent);

    _sut.AddJoypadEventListener(&joypadBtnDownEvent);
    EXPECT_EQ(_sut.joyButtonDownList.back(), &joypadBtnDownEvent);
    _sut.RemoveJoypadEventListener(&joypadBtnDownEvent);

    EXPECT_FALSE(_sut.joyButtonDownList.size() <= 0);
    EXPECT_NE(_sut.joyButtonDownList.back(), &joypadBtnDownEvent);

    _sut.AddJoypadEventListener(&joypadBtnTriggerEvent);
    EXPECT_EQ(_sut.joyButtonTriggerList.back(), &joypadBtnTriggerEvent);
    _sut.RemoveJoypadEventListener(&joypadBtnTriggerEvent);

    EXPECT_FALSE(_sut.joyButtonTriggerList.size() <= 0);
    EXPECT_NE(_sut.joyButtonTriggerList.back(), &joypadBtnTriggerEvent);
}

TEST_F(utEventHandler, onMouseMoveShouldSendEventData)
{
    SDL_Event event;

    int x = 3;
    int y = 6;

    performMoveMouse(event, 1);

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_sdlMock, SDL_GetMouseState(_, _))
        .WillRepeatedly(
            DoAll(SetArgPointee<0>(x), SetArgPointee<1>(y), Return(0)));
    EXPECT_CALL(_mouseEventMock, MouseMove(_));

    _sut.PollEvent(&_windowMock);
}

TEST_F(utEventHandler, onJoystickAddedFailedOpenTest)
{

    SDL_Event event;
    event.type = SDL_JOYDEVICEADDED;
    event.jdevice.which = 0;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    _sut.PollEvent(&_windowMock);

    event.type = SDL_JOYDEVICEREMOVED;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    _sut.PollEvent(&_windowMock);
}

TEST_F(utEventHandler, onJoystickAddedSuccessOpenTest)
{
    SDL_Joystick joystick;
    SDL_Event event;
    event.type = SDL_JOYDEVICEADDED;
    event.jdevice.which = 0;

    EXPECT_CALL(_sdlMock, SDL_JoystickOpen(_)).WillOnce(Return(&joystick));
    EXPECT_CALL(_sdlMock, SDL_JoystickClose(&joystick));

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    _sut.PollEvent(&_windowMock);

    event.type = SDL_JOYDEVICEREMOVED;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    _sut.PollEvent(&_windowMock);
}

TEST_F(utEventHandler, onJoystickButtonPressedTest)
{
    NiceMock<doengine::mocks::JoypadMock> joypadMock;
    SDL_Joystick joystick;
    SDL_Event event;
    event.type = SDL_JOYBUTTONDOWN;
    event.jbutton.which = 0;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_joyButtonDownMock, OnButtonDown(_)).Times(0);

    _sut.PollEvent(&_windowMock);

    event.type = SDL_JOYBUTTONUP;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_joyButtonUpMock, OnButtonUp(_)).Times(0);

    _sut.PollEvent(&_windowMock);

    _sut.joypadsConnected[event.jbutton.which] = &joypadMock;

    event.type = SDL_JOYBUTTONDOWN;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_joyButtonDownMock, OnButtonDown(_));

    _sut.PollEvent(&_windowMock);

    event.type = SDL_JOYBUTTONUP;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_joyButtonUpMock, OnButtonUp(_));

    _sut.PollEvent(&_windowMock);

    _sut.joypadsConnected.clear();
}

TEST_F(utEventHandler, onJoystickTriggerTest)
{
    NiceMock<doengine::mocks::JoypadMock> joypadMock;
    SDL_Joystick joystick;
    SDL_Event event;

    event.type = SDL_JOYAXISMOTION;
    event.jaxis.which = 0;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_joyButtonTriggerMock, OnButtonTriggered(_)).Times(0);

    _sut.PollEvent(&_windowMock);

    _sut.joypadsConnected[event.jaxis.which] = &joypadMock;

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_joyButtonTriggerMock, OnButtonTriggered(_));

    _sut.PollEvent(&_windowMock);

    _sut.joypadsConnected.clear();
}

class utEventHandlerMouseClick
    : public utEventHandler,
      public WithParamInterface<
          std::tuple<unsigned int, MouseButton, unsigned char>>
{
  public:
    utEventHandlerMouseClick() : utEventHandler()
    {
    }

    void SetUp() override
    {
        utEventHandler::SetUp();
    }

    void TearDown() override
    {
        utEventHandler::TearDown();
    }
};

INSTANTIATE_TEST_CASE_P(
    utEventHandlerMouseClickTestSuite, utEventHandlerMouseClick,
    Values(std::make_tuple(SDL_MOUSEBUTTONDOWN, MouseButton::Left,
                           SDL_BUTTON_LEFT),
           std::make_tuple(SDL_MOUSEBUTTONDOWN, MouseButton::Right,
                           SDL_BUTTON_RIGHT),
           std::make_tuple(SDL_MOUSEBUTTONDOWN, MouseButton::Middle,
                           SDL_BUTTON_MIDDLE),
           std::make_tuple(SDL_MOUSEBUTTONDOWN, MouseButton::X1, SDL_BUTTON_X1),
           std::make_tuple(SDL_MOUSEBUTTONDOWN, MouseButton::X2, SDL_BUTTON_X2),
           std::make_tuple(SDL_MOUSEBUTTONUP, MouseButton::Left,
                           SDL_BUTTON_LEFT),
           std::make_tuple(SDL_MOUSEBUTTONUP, MouseButton::Right,
                           SDL_BUTTON_RIGHT),
           std::make_tuple(SDL_MOUSEBUTTONUP, MouseButton::Middle,
                           SDL_BUTTON_MIDDLE),
           std::make_tuple(SDL_MOUSEBUTTONUP, MouseButton::X1, SDL_BUTTON_X1),
           std::make_tuple(SDL_MOUSEBUTTONUP, MouseButton::X2, SDL_BUTTON_X2))

);

TEST_P(utEventHandlerMouseClick, onMouseClickShouldSendEventData)
{
    SDL_Event event;
    const unsigned int mouseEventType = std::get<0>(GetParam());
    const MouseButton mouseButton = std::get<1>(GetParam());
    const unsigned char sdl_button_id = std::get<2>(GetParam());
    std::bitset<Mouse::BUTTONS_COUNT> mouseBtnBitset;

    performMoveClick(event, mouseEventType, 1, sdl_button_id);

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_sdlMock, SDL_GetMouseState(_, _))
        .WillRepeatedly(DoAll(SetArgPointee<0>(1), SetArgPointee<1>(2),
                              Return(sdl_button_id)));

    if (mouseEventType == SDL_MOUSEBUTTONDOWN)
    {
        EXPECT_CALL(_mouseEventMock, MouseButtonDown(_))
            .WillOnce(Invoke([&](const Mouse& mouse) {
                mouse.getButtonStateBitset(mouseBtnBitset);
                EXPECT_TRUE(
                    mouseBtnBitset.test(static_cast<std::size_t>(mouseButton)));
            }));
    }
    else
    {
        EXPECT_CALL(_mouseEventMock, MouseButtonUp(_))
            .WillOnce(Invoke([&](const Mouse& mouse) {
                mouse.getButtonStateBitset(mouseBtnBitset);
                EXPECT_TRUE(
                    mouseBtnBitset.test(static_cast<std::size_t>(mouseButton)));
            }));
    }

    _sut.PollEvent(&_windowMock);
}

class utEventHandlerKeyboard
    : public utEventHandler,
      public WithParamInterface<
          std::tuple<const unsigned int, const unsigned short,
                     const unsigned char, const unsigned short>>
{
  public:
    utEventHandlerKeyboard() : utEventHandler()
    {
    }

    void SetUp()
    {
        utEventHandler::SetUp();
    }
};

INSTANTIATE_TEST_CASE_P(
    utEventHandlerKeyboardTestSuite, utEventHandlerKeyboard,
    Values(
        std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_A, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_B, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_C, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_D, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_E, SDL_PRESSED, KMOD_SHIFT),
        std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_F, SDL_PRESSED, KMOD_RSHIFT),
        std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_G, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_H, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_I, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_J, SDL_RELEASED, KMOD_LSHIFT),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_K, SDL_PRESSED, KMOD_LALT),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_L, SDL_RELEASED, KMOD_RALT),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_M, SDL_PRESSED, KMOD_NUM),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_N, SDL_RELEASED, KMOD_CAPS),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_O, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_P, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_Q, SDL_PRESSED, KMOD_ALT),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_R, SDL_RELEASED, KMOD_SCROLL),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_S, SDL_PRESSED, KMOD_CTRL),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_T, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_V, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_W, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_X, SDL_PRESSED, KMOD_RGUI),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_Y, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_Z, SDL_PRESSED, KMOD_LGUI),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_0, SDL_PRESSED, KMOD_GUI),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_1, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_2, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_3, SDL_PRESSED, KMOD_MODE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_4, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_5, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_6, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_7, SDL_RELEASED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_8, SDL_PRESSED, KMOD_NONE),
        std::make_tuple(SDL_KEYUP, SDL_SCANCODE_9, SDL_RELEASED, KMOD_NONE)));

TEST_P(utEventHandlerKeyboard, onKeyboardPressShouldSendKeypressed)
{
    SDL_Event event;

    performKeyPress(event, std::get<0>(GetParam()), std::get<1>(GetParam()),
                    std::get<2>(GetParam()), std::get<3>(GetParam()));

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    if (std::get<0>(GetParam()) == SDL_KEYDOWN)
        EXPECT_CALL(_keyDownEventMock, OnKeydown(_));
    else
        EXPECT_CALL(_keyUpEventMock, OnKeyup(_));

    _sut.PollEvent(&_windowMock);
}

