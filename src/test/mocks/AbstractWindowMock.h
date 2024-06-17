
#pragma once
#include "Color.h"
#include <gmock/gmock-function-mocker.h>

namespace doengine::mocks
{
#if TO_FIX
class WindowManagerMock : public WindowManager
{
  public:
    MOCK_METHOD(const bool, IsRunning, (), (const, override));
    MOCK_METHOD(Renderer*, getRender, (), (const, override));
    MOCK_METHOD(WindowManager*, setFullScreen, (), (override));
    MOCK_METHOD(WindowManager*, setWindowMode, (), (override));
    MOCK_METHOD(WindowManager*, PollEvent, (), (override));
    MOCK_METHOD(WindowManager*, Update, (), (override));
    MOCK_METHOD(WindowManager*, Render, (), (override));
    MOCK_METHOD(WindowManager*, Quit, (), (override));
    MOCK_METHOD(int, getH, (), (override));
    MOCK_METHOD(int, getW, (), (override));
    MOCK_METHOD(WindowManager*, SetWindowPencilColor, (Color), (override));
};
#endif
} // namespace doengine::mocks