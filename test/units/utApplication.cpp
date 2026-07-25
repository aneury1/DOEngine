#include "Application.h"
#include "fixtures/DoEngineFixture.h"
#include "mocks/SDLMock.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>

namespace doengine
{

namespace ut
{
class utApplication : public testing::Test
{
  public:
    utApplication() : xsdlMock()
    {
    }

    ~utApplication()
    {
    }

    /*Not constructable use getApplication method to get an instance*/
    // Application _sut;
    void SetUp() override
    {
        testing::Test::SetUp();
        SetSDLMock(&xsdlMock);
        /// ON_CALL(xsdlMock, SDL_GetTicks()).WillByDefault(Return(0));
    }

    testing::NiceMock<mocks::SDLMock> xsdlMock;
};

} // namespace ut

} // namespace doengine