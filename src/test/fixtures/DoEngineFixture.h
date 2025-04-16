#pragma once

///#include "mocks/WindowManagerMock.h"
#include "mocks/SDLMock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::_;
using testing::NiceMock;
using testing::Return;

namespace doengine
{
namespace fixture
{
class DoEngineFixture : public testing::Test
{
  public:
    DoEngineFixture() : _sdlMock() ///, _windowMock()
    {
        SetSDLMock(&_sdlMock);

        ON_CALL(_sdlMock, SDL_GetMouseState(_, _)).WillByDefault(Return(0u));
    }
    void SetUp() override
    {
        Test::SetUp();
    }

    NiceMock<mocks::SDLMock> _sdlMock;
    /// NiceMock<mocks::WindowManagerMock> _windowMock;
};
} // namespace fixture
} // namespace doengine