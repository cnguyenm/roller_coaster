#include "Camera.h"

#include "pch.h"

Camera::Camera()
{
}

void Camera::apply()
{
	gluLookAt(
		this->pos.x, this->pos.y, this->pos.z,
		0, 0, 0,  // center x,y,z
		0, 1, 0  // up vector
	);
}


