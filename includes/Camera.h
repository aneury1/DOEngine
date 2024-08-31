#pragma once

#include "Camera.h"

namespace doengine
{

class Camera
{
    //   Vector<int> camera_pos;

  public:
    enum class CameraMovement : unsigned char
    {
        CameraUp,
        CameraDown,
        CameraLeft,
        CameraRight,
        CameraNotMovement
    };

    virtual Camera* Update(CameraMovement where) = 0;
};

} // namespace doengine
