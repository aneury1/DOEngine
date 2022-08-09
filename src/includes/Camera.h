#pragma once
#include <Vector>
#include <Window.h>


class Camera
{
	Vector<int> camera_pos;
public:

	Camera(Window* window);
	Camera(Window* window,const Vector<int>& current_pos);
	~Camera();

};

