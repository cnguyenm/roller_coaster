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

	// instead of rotate cam
	// rotate the world
	// dir: counter-clockwise
	glRotated(this->angle_y_axis, 0, 1, 0);
	glRotated(this->angle_x_axis, 1, 0, 0);
}

void Camera::move_relative(double x, double y, double z)
{
	this->pos += Vec3(x, y, z);
	this->center += Vec3(x, y, z);
}

void Camera::rotate_around_yaxis(double value)
{
	//pos.x += 2;
	this->angle_y_axis += value;
}

void Camera::rotate_around_xaxis(double value)
{
	this->angle_x_axis += value;
}

void Camera::move_to(Vec3 pos)
{
	Vec3 dir = pos - this->pos;
	this->center += dir;

	this->pos = pos;
	
}

void Camera::look_at(Vec3 pos)
{
	this->center = pos;
}

// should be called, after other objects update()
void Camera::update()
{
	this->pos = ball->pos;
	this->pos.y += ball->size;
	this->pos.x += ball->size / 3;
	this->look_at(pos + ball->vel.normalized() );
}

void Camera::set_ball(GameObject * ball)
{
	this->ball = ball;
}


