
#pragma once
#include "Color.h"
#include <gmock/gmock-function-mocker.h>

namespace doengine::mocks
{

class AbstractWindowMock : public AbstractWindow
{
  public:
    MOCK_METHOD(const bool, IsRunning, (), (const, override));
    MOCK_METHOD(gfx::Renderer*, getRender, (), (const, override));
    MOCK_METHOD(AbstractWindow*, setFullScreen, (), (override));
    MOCK_METHOD(AbstractWindow*, setWindowMode, (), (override));
    MOCK_METHOD(AbstractWindow*, PollEvent, (), (override));
    MOCK_METHOD(AbstractWindow*, Update, (), (override));
    MOCK_METHOD(AbstractWindow*, Render, (), (override));
    MOCK_METHOD(AbstractWindow*, Quit, (), (override));
    MOCK_METHOD(int, getH, (), (override));
    MOCK_METHOD(int, getW, (), (override));
    MOCK_METHOD(AbstractWindow*, SetWindowPencilColor, (Color), (override));
};

} // namespace doengine::mocks