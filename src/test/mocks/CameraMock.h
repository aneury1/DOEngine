#pragma once

#include "Camera.h"
#include <gmock/gmock-function-mocker.h>

namespace doengine::mocks
{

using doengine::Camera;

class CameraMock : public Camera
{
  public:
    MOCK_METHOD(Camera*, Update, (CameraMovement), (override));
};

} // namespace doengine::mocks