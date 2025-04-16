#include "Mouse.h"
#include "SDLMouse.h"
#include "fixtures/DoEngineFixture.h"
#include "mocks/SDLMock.h"
#include "v2d_vector.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <bitset>
#include <cstddef>
#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tuple>

namespace doengine
{
namespace ut
{
using doengine::devices::Mouse;
using doengine::devices::MouseButton;
using doengine::devices::SDLMouse;
using doengine::fixture::DoEngineFixture;
using namespace testing;

static_assert(static_cast<int>(MouseButton::Left) == SDL_BUTTON_LEFT,
              "SDL_BUTTON_LEFT mismatch");
static_assert(static_cast<int>(MouseButton::Right) == SDL_BUTTON_RIGHT,
              "SDL_BUTTON_RIGHT mismatch");
static_assert(static_cast<int>(MouseButton::Middle) == SDL_BUTTON_MIDDLE,
              "SDL_BUTTON_MIDDLE mismatch");
static_assert(static_cast<int>(MouseButton::X1) == SDL_BUTTON_X1,
              "SDL_BUTTON_X1 mismatch");
static_assert(static_cast<int>(MouseButton::X2) == SDL_BUTTON_X2,
              "SDL_BUTTON_X2 mismatch");

class utSDLMouse : public DoEngineFixture
{
  public:
    utSDLMouse() : DoEngineFixture(), _sut(0, 0, Point{0, 0})
    {
    }

    void SetUp() override
    {
        DoEngineFixture::SetUp();
    }

    SDLMouse _sut;
};

TEST_F(utSDLMouse, isRightClickedTest)
{
    ON_CALL(_sdlMock, SDL_GetMouseState(_, _))
        .WillByDefault(Return(SDL_BUTTON_RMASK));
    _sut.updateValues();
    EXPECT_TRUE(_sut.isRightClick());
}

TEST_F(utSDLMouse, isLeftClickedTest)
{
    ON_CALL(_sdlMock, SDL_GetMouseState(_, _))
        .WillByDefault(Return(SDL_BUTTON_LMASK));
    _sut.updateValues();
    EXPECT_TRUE(_sut.isLeftClick());
}

TEST_F(utSDLMouse, isMiddleClickedTest)
{
    ON_CALL(_sdlMock, SDL_GetMouseState(_, _))
        .WillByDefault(Return(SDL_BUTTON_MMASK));
    _sut.updateValues();
    EXPECT_TRUE(_sut.isMiddleClick());
}

TEST_F(utSDLMouse, getMousePositionTest)
{
    Point p{0, 0};
    const int expectedX = 25;
    const int expectedY = 52;

    ON_CALL(_sdlMock, SDL_GetMouseState(_, _))
        .WillByDefault(DoAll(SetArgPointee<0>(expectedX),
                             SetArgPointee<1>(expectedY),
                             Return(SDL_BUTTON_MMASK)));

    _sut.updateValues();
    _sut.getPosition(p);

    EXPECT_EQ(p.x, expectedX);
    EXPECT_EQ(p.y, expectedY);
}

class utSDLMouseBitmapTest
    : public utSDLMouse,
      public WithParamInterface<std::tuple<MouseButton, unsigned>>
{
};

INSTANTIATE_TEST_SUITE_P(utSDLMouseBitmapTestSuite, utSDLMouseBitmapTest,
                         Values(std::make_tuple(MouseButton::Right, 3u),
                                std::make_tuple(MouseButton::Left, 1u),
                                std::make_tuple(MouseButton::Middle, 2u),
                                std::make_tuple(MouseButton::X1, 4u),
                                std::make_tuple(MouseButton::X2, 5u)));

TEST_P(utSDLMouseBitmapTest, getMouseButtonsBitmapTest)
{
    std::bitset<Mouse::BUTTONS_COUNT> result;
    unsigned sdlValue = std::get<1>(GetParam());
    auto mouseButtonPressed = std::get<0>(GetParam());
    auto bitsetIdx = static_cast<std::size_t>(mouseButtonPressed);

    ON_CALL(_sdlMock, SDL_GetMouseState(_, _)).WillByDefault(Return(sdlValue));
    _sut.updateValues();
    _sut.getButtonStateBitset(result);

    EXPECT_TRUE(result.test(bitsetIdx));
}

// TEST_F(utSDLMouse, isRightClickedTest)
// TEST_F(utSDLMouse, isRightClickedTest)
// TEST_F(utSDLMouse, isRightClickedTest)

} // namespace ut
} // namespace doengine