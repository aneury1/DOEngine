#pragma once

#include "Camera.h"
#include <gmock/gmock-function-mocker.h>

 

class CameraMock : public Camera
{
  public:
    MOCK_METHOD(Camera*, Update, (CameraMovement), (override));
};
