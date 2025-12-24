#include "SpriteOffset.h"
#include "mocks/FPSManagerMock.h"
#include "mocks/SDLMock.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

namespace doengine
{
namespace ut
{

using testing::_;
using testing::Return;

class utSpriteOffset : public testing::Test
{
  public:
    utFPSManager() : xsdlMock()
    {
    }

    SpriteAnimationOffset _sut;
    void SetUp() override
    {
        testing::Test::SetUp();
        SetSDLMock(&xsdlMock);
        ON_CALL(xsdlMock, SDL_GetTicks()).WillByDefault(Return(0));
    }

    testing::NiceMock<mocks::SDLMock> xsdlMock;
};

}

}