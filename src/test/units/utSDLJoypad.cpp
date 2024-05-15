#include "SDLJoypad.h"
#include "abstract/devices/Joypad.h"
#include "fixtures/DoEngineFixture.h"
#include "mocks/SDLMock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tuple>
#include <vector>


static_assert(static_cast<int>(PowerLevel::Unknown) ==
                  SDL_JOYSTICK_POWER_UNKNOWN,
              "SDL_JOYSTICK_POWER_UNKNOWN mismatch");
static_assert(static_cast<int>(PowerLevel::Empty) == SDL_JOYSTICK_POWER_EMPTY,
              "SDL_JOYSTICK_POWER_EMPTY mismatch");
static_assert(static_cast<int>(PowerLevel::Low) == SDL_JOYSTICK_POWER_LOW,
              "SDL_JOYSTICK_POWER_LOW mismatch");
static_assert(static_cast<int>(PowerLevel::Medium) == SDL_JOYSTICK_POWER_MEDIUM,
              "SDL_JOYSTICK_POWER_MEDIUM mismatch");
static_assert(static_cast<int>(PowerLevel::Full) == SDL_JOYSTICK_POWER_FULL,
              "SDL_JOYSTICK_POWER_FULL mismatch");
static_assert(static_cast<int>(PowerLevel::Wired) == SDL_JOYSTICK_POWER_WIRED,
              "SDL_JOYSTICK_POWER_WIRED mismatch");
static_assert(static_cast<int>(PowerLevel::Max) == SDL_JOYSTICK_POWER_MAX,
              "SDL_JOYSTICK_POWER_MAX mismatch");

const char* JOYSTICK_NAME = "DOENGINE_JOYSTICK";
const char* NO_NAME = "NOT_FOUND";

class utSDLJoypad : public DoEngineFixture
{
  public:
    utSDLJoypad() : DoEngineFixture(), _sut(nullptr)
    {
    }

    void SetUp() override
    {
        DoEngineFixture::SetUp();

        ON_CALL(_sdlMock, SDL_JoystickName(_))
            .WillByDefault(Return(JOYSTICK_NAME));
        ON_CALL(_sdlMock, SDL_JoystickCurrentPowerLevel(_))
            .WillByDefault(Return(SDL_JOYSTICK_POWER_UNKNOWN));
        ON_CALL(_sdlMock, SDL_JoystickInstanceID(_)).WillByDefault(Return(0));
        ON_CALL(_sdlMock, SDL_JoystickGetPlayerIndex(_))
            .WillByDefault(Return(0));
        ON_CALL(_sdlMock, SDL_JoystickNumButtons(_)).WillByDefault(Return(0));
        ON_CALL(_sdlMock, SDL_JoystickNumAxes(_)).WillByDefault(Return(0));
        ON_CALL(_sdlMock, SDL_JoystickGetButton(_, _)).WillByDefault(Return(0));
        ON_CALL(_sdlMock, SDL_JoystickGetAxis(_, _)).WillByDefault(Return(0));
    }

    SDLJoypad _sut;
};

TEST_F(utSDLJoypad, joystickNameTest)
{
    std::string joypadName;
    _sut.getName(joypadName);

    EXPECT_STREQ(joypadName.c_str(), JOYSTICK_NAME);

    ON_CALL(_sdlMock, SDL_JoystickName(_)).WillByDefault(Return(nullptr));
    _sut.getName(joypadName);

    EXPECT_STREQ(joypadName.c_str(), NO_NAME);
}

TEST_F(utSDLJoypad, joystickInstanceIdTest)
{
    int id = 1;
    ON_CALL(_sdlMock, SDL_JoystickInstanceID(_)).WillByDefault(Return(id));
    EXPECT_EQ(_sut.getId(), id);

    id = -1;

    ON_CALL(_sdlMock, SDL_JoystickInstanceID(_)).WillByDefault(Return(id));
    EXPECT_EQ(_sut.getId(), id);
}

TEST_F(utSDLJoypad, joystickGetPlayerIndexTest)
{
    int index = 1;

    ON_CALL(_sdlMock, SDL_JoystickGetPlayerIndex(_))
        .WillByDefault(Return(index));
    EXPECT_EQ(_sut.getPlayerIndex(), index);

    index = -1;
    ON_CALL(_sdlMock, SDL_JoystickGetPlayerIndex(_))
        .WillByDefault(Return(index));
    EXPECT_EQ(_sut.getPlayerIndex(), index);
}

TEST_F(utSDLJoypad, joystickGetNumberOfButtonsTest)
{
    int buttons = 1;

    ON_CALL(_sdlMock, SDL_JoystickNumButtons(_)).WillByDefault(Return(buttons));
    EXPECT_EQ(_sut.getNumberOfButtons(), buttons);

    buttons = 0;
    ON_CALL(_sdlMock, SDL_JoystickNumButtons(_)).WillByDefault(Return(buttons));
    EXPECT_EQ(_sut.getNumberOfButtons(), buttons);
}

TEST_F(utSDLJoypad, joystickGetNumberOfAxesTest)
{
    int axes = 1;

    ON_CALL(_sdlMock, SDL_JoystickNumAxes(_)).WillByDefault(Return(axes));
    EXPECT_EQ(_sut.getNumberOfAxes(), axes);

    axes = 0;
    ON_CALL(_sdlMock, SDL_JoystickNumAxes(_)).WillByDefault(Return(axes));
    EXPECT_EQ(_sut.getNumberOfAxes(), axes);
}

TEST_F(utSDLJoypad, joystickGetButtonsPressedTest)
{
    std::vector<bool> buttonStates;
    const int buttons = 4;

    ON_CALL(_sdlMock, SDL_JoystickNumButtons(_)).WillByDefault(Return(buttons));

    _sut.getJoypadButtonsPressed(buttonStates);
    EXPECT_EQ(buttonStates[0], false);
    EXPECT_EQ(buttonStates[1], false);
    EXPECT_EQ(buttonStates[2], false);
    EXPECT_EQ(buttonStates[3], false);

    ON_CALL(_sdlMock, SDL_JoystickGetButton(_, 0)).WillByDefault(Return(1));
    ON_CALL(_sdlMock, SDL_JoystickGetButton(_, 2)).WillByDefault(Return(1));

    _sut.getJoypadButtonsPressed(buttonStates);

    EXPECT_EQ(buttonStates[0], true);
    EXPECT_EQ(buttonStates[1], false);
    EXPECT_EQ(buttonStates[2], true);
    EXPECT_EQ(buttonStates[3], false);
}

TEST_F(utSDLJoypad, joystickGetAxisValueTest)
{
    const int axes = 4;
    const short axisValue = 100;

    ON_CALL(_sdlMock, SDL_JoystickNumAxes(_)).WillByDefault(Return(axes));
    ON_CALL(_sdlMock, SDL_JoystickGetAxis(_, 0))
        .WillByDefault(Return(axisValue));
    ON_CALL(_sdlMock, SDL_JoystickGetAxis(_, 1))
        .WillByDefault(Return(axisValue * (-1)));

    EXPECT_EQ(_sut.getAxisValue(0), axisValue);
    EXPECT_EQ(_sut.getAxisValue(1), axisValue * (-1));
}

TEST_F(utSDLJoypad, joystickStartRumbleTest)
{
    unsigned short left = 3;
    unsigned short right = 4;
    unsigned int duration_ms = 2;

    ON_CALL(_sdlMock, SDL_JoystickHasRumble(_)).WillByDefault(Return(SDL_TRUE));
    EXPECT_CALL(_sdlMock, SDL_JoystickRumble(_, left, right, duration_ms));

    _sut.startRumble(left, right, duration_ms);

    ON_CALL(_sdlMock, SDL_JoystickHasRumble(_))
        .WillByDefault(Return(SDL_FALSE));
    EXPECT_CALL(_sdlMock, SDL_JoystickRumble(_, _, _, _)).Times(0);

    _sut.startRumble(left, right, duration_ms);
}

class utSDLJoypadPowerLevel
    : public utSDLJoypad,
      public WithParamInterface<std::tuple<PowerLevel, SDL_JoystickPowerLevel>>
{
};

INSTANTIATE_TEST_SUITE_P(
    utSDLJoypadPowerLevelTestSuite, utSDLJoypadPowerLevel,
    Values(std::make_tuple(PowerLevel::Unknown, SDL_JOYSTICK_POWER_UNKNOWN),
           std::make_tuple(PowerLevel::Empty, SDL_JOYSTICK_POWER_EMPTY),
           std::make_tuple(PowerLevel::Low, SDL_JOYSTICK_POWER_LOW),
           std::make_tuple(PowerLevel::Medium, SDL_JOYSTICK_POWER_MEDIUM),
           std::make_tuple(PowerLevel::Full, SDL_JOYSTICK_POWER_FULL),
           std::make_tuple(PowerLevel::Wired, SDL_JOYSTICK_POWER_WIRED),
           std::make_tuple(PowerLevel::Max, SDL_JOYSTICK_POWER_MAX)));

TEST_P(utSDLJoypadPowerLevel, joystickGetCurrentPowerLevel)
{
    const auto param = GetParam();
    ON_CALL(_sdlMock, SDL_JoystickCurrentPowerLevel(_))
        .WillByDefault(Return(std::get<1>(param)));
    EXPECT_EQ(_sut.getPowerLevel(), std::get<0>(param));
}

