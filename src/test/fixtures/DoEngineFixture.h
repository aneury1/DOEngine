#pragma once

#include "mocks/AbstractWindowMock.h"
#include "mocks/SDLMock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::_;
using testing::NiceMock;
using testing::Return;

class DoEngineFixture : public testing::Test
{
  public:
    DoEngineFixture() : _sdlMock(), _windowMock()
    {
    }
    void SetUp() override
    {
        Test::SetUp();
        SetSDLMock(&_sdlMock);
    }

    NiceMock<mocks::SDLMock> _sdlMock;
    NiceMock<mocks::AbstractWindowMock> _windowMock;
};
