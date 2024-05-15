#include "FPSManager.h"
#include "mocks/FPSManagerMock.h"
#include "mocks/SDLMock.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

namespace doengine::ut
{

using testing::_;
using testing::Return;

class utFPSManager : public testing::Test
{
  public:
    utFPSManager() : xsdlMock()
    {
    }

    FpsManager _sut;
    void SetUp() override
    {
        testing::Test::SetUp();
        SetSDLMock(&xsdlMock);
        ON_CALL(xsdlMock, SDL_GetTicks()).WillByDefault(Return(0));
    }

    testing::NiceMock<mocks::SDLMock> xsdlMock;
};

TEST_F(utFPSManager, doengineGetElapsedTimeTest)
{
    ON_CALL(*sdlMock, SDL_GetTicks()).WillByDefault(Return(1500U));
    _sut.Handle();
    // testing::Mock::AllowLeak(&sdlMock);
}

TEST_F(utFPSManager, doengineStartTimerAndGetElapseTime)
{
    EXPECT_CALL(xsdlMock, SDL_GetTicks())
        .WillOnce(Return(5U))
        .WillOnce(Return(15U));

    _sut.Start();
    _sut.Handle();

    EXPECT_FLOAT_EQ(_sut.getElapsedTime(), 10U);
}

TEST_F(utFPSManager, doengineHandleTest)
{
    EXPECT_CALL(xsdlMock, SDL_GetTicks())
        .WillOnce(Return(5U))
        .WillOnce(Return(15U));
    EXPECT_CALL(xsdlMock, SDL_Delay(6));

    _sut.Start();
    _sut.Handle();

    EXPECT_FLOAT_EQ(_sut.getElapsedTime(), 10U);

    EXPECT_CALL(xsdlMock, SDL_GetTicks())
        .WillOnce(Return(5U))
        .WillOnce(Return(25U));
    EXPECT_CALL(xsdlMock, SDL_Delay(_)).Times(0);

    _sut.Start();
    _sut.Handle();

    EXPECT_FLOAT_EQ(_sut.getElapsedTime(), 20U);

    EXPECT_CALL(xsdlMock, SDL_GetTicks())
        .WillOnce(Return(5U))
        .WillOnce(Return(14U));
    EXPECT_CALL(xsdlMock, SDL_Delay(6));

    _sut.setFPS(65);
    _sut.Start();
    _sut.Handle();

    EXPECT_FLOAT_EQ(_sut.getElapsedTime(), 9);
}

} // namespace doengine::ut
