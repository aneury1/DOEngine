#include "Event.h"
#include "EventHandler.h"
#include "fixtures/DoEngineFixture.h"
#include "mocks/EventHandlerMock.h"
#include "mocks/SDLMock.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <tuple>

namespace doengine::ut
{

using doengine::fixture::DoEngineFixture;

using namespace testing;

// TODO issue-27
// static_assert(MouseButton::Left == SDL_BUTTON_LEFT, "SDL_BUTTON_LEFT
// mismatch"); static_assert(MouseButton::Left == SDL_BUTTON_RIGHT,
//               "SDL_BUTTON_RIGHT mismatch");
// static_assert(MouseButton::Left == SDL_BUTTON_MIDDLE,
//               "SDL_BUTTON_MIDDLE mismatch");
// static_assert(MouseButton::Left == SDL_BUTTON_X1, "SDL_BUTTON_X1 mismatch");
// static_assert(MouseButton::Left == SDL_BUTTON_X2, "SDL_BUTTON_X2 mismatch");

class utEventHandler : public DoEngineFixture
{
  public:
    utEventHandler()
        : DoEngineFixture(), _mouseEventMock(), _keyUpEventMock(),
          _keyDownEventMock()
    {
    }

    void SetUp() override
    {
        DoEngineFixture::SetUp();
        ON_CALL(_sdlMock, SDL_PollEvent(_)).WillByDefault(Return(0));
        _sut.AddMouseEvent(&_mouseEventMock);
        _sut.AddKeyPressEventListener(&_keyUpEventMock);
        _sut.AddKeyPressEventListener(&_keyDownEventMock);
    }

    void TearDown() override
    {
        _sut.RemovedMouseEvent(&_mouseEventMock);
        _sut.RemoveKeyPressEventListener(&_keyUpEventMock);
        _sut.RemoveKeyPressEventListener(&_keyDownEventMock);
    }

    void performMoveMouse(SDL_Event& event, const unsigned int which)
    {
        event.type = SDL_MOUSEMOTION;
        event.motion.which = 1;
    }

    void performMoveClick(SDL_Event& event, const unsigned int which,
                          const unsigned char button)
    {
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
};

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

    EXPECT_CALL(_mouseEventMock, MouseMove(event.motion.which, x, y));

    _sut.PollEvent(&_windowMock);
}

class utEventHandlerMouseClick
    : public utEventHandler,
      public WithParamInterface<std::tuple<MouseButton, unsigned char>>
{
};

INSTANTIATE_TEST_CASE_P(
    utEventHandlerMouseClickTestSuite, utEventHandlerMouseClick,
    Values(
        // std::make_tuple(MouseButton::Left, SDL_BUTTON_LEFT),
        //    std::make_tuple(MouseButton::Right, SDL_BUTTON_RIGHT),
        //    std::make_tuple(MouseButton::Middle, SDL_BUTTON_MIDDLE),
        //    std::make_tuple(MouseButton::X1, SDL_BUTTON_X1),
        //    std::make_tuple(MouseButton::X2, SDL_BUTTON_X2)
        ));

// TODO issue-27: Enable this test
TEST_P(utEventHandlerMouseClick, DISALBLED_onMouseClickShouldSendEventData)
{
    SDL_Event event;
    MouseButton mouseButton = std::get<0>(GetParam());
    unsigned char sdl_button_id = std::get<1>(GetParam());

    // performMoveClick(event, 1, sdl_button_id); TODO issue-27 uncommend

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    EXPECT_CALL(_sdlMock, SDL_GetMouseState(_, _))
        .WillRepeatedly(
            DoAll(SetArgPointee<0>(1), SetArgPointee<1>(2), Return(0)));

    EXPECT_CALL(_mouseEventMock,
                MouseButtonDown(event.motion.which, mouseButton));

    _sut.PollEvent(&_windowMock);
}

class utEventHandlerKeyboard
    : public utEventHandler,
      public WithParamInterface<
          std::tuple<const unsigned int, const unsigned short,
                     const unsigned char, const unsigned short>>
{
};

INSTANTIATE_TEST_CASE_P(
    utEventHandlerKeyboardTestSuite, utEventHandlerKeyboard,
    Values(std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_A, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_B, SDL_RELEASED, KMOD_NONE),
           std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_C, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_D, SDL_RELEASED, KMOD_NONE),
           std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_E, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_F, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_G, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_H, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_I, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_J, SDL_RELEASED,
                           KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_K, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_L, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_M, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_N, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_O, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_P, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_Q, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_R, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_S, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_T, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_V, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_W, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_X, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_Y, SDL_PRESSED, KMOD_NONE),
           std::make_tuple(SDL_KEYUP, SDL_SCANCODE_Z, SDL_PRESSED, KMOD_NONE)));

TEST_P(utEventHandlerKeyboard, onKeyboardPressShouldSendKeypressed)
{
    SDL_Event event;

    performKeyPress(event, std::get<0>(GetParam()), std::get<1>(GetParam()),
                    std::get<2>(GetParam()), std::get<3>(GetParam()));

    EXPECT_CALL(_sdlMock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(event), Return(1)))
        .WillOnce(Return(0));

    _sut.PollEvent(&_windowMock);
}

}; // namespace doengine::ut