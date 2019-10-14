#include "Camera.h"

#include "pch.h"

Camera::Camera()
{
	center = Vec3(0, 0, 0);
}

void Camera::apply()
{
	gluLookAt(
		pos.x, pos.y, pos.z,
		center.x, center.y, center.z,  // center x,y,z
		0, 1, 0  // up vector
	);
}

void Camera::move_left(double value)
{
	pos.x -= value;
	center.x -= value;
}

void Camera::move_right(double value)
{
	pos.x += value;
	center.x += value;
}

void Camera::move_up(double value)
{
	pos.y += value;
	center.y += value;
}

void Camera::move_down(double value)
{
	pos.y -= value;
	center.y -= value;
}


