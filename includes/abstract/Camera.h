#pragma once


#include "abstract/Camera.h"

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

    //   Camera(AbstractWindow *window);
    //   Camera(AbstractWindow *window, const Vector<int> &current_pos);
    //   virtual ~Camera();

    virtual Camera* Update(CameraMovement where) = 0;
};

} // namespace doengine
