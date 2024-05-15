#pragma once
#include "Renderer.h"
#include <gmock/gmock-function-mocker.h>

class RendererMock : public gfx::Renderer
{
  public:
    MOCK_METHOD(bool, isRenderOk, (), (override));
    MOCK_METHOD(void*, getNativeRenderer, (), (override));
    MOCK_METHOD(void, destroy, (), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, setDrawColor, (doengine::Color), (override));
    MOCK_METHOD(void, present, (), (override));
};
