#pragma once
#include "GameObject.h"

class Camera :
	public GameObject
{
public:

	Vec3 center;  // center to look at

	Camera();
	void apply();

	// affect camera+center position
	void move_left(double value);
	void move_right(double value);
	void move_up(double value);
	void move_down(double value);

	// move relative with cur pos
	void move_relative(double x, double y, double z);
	void rotate_around_yaxis(double value);
	void rotate_around_xaxis(double value);

	// move to pos, also affect camera_center
	void move_to(Vec3 pos);
	void look_at(Vec3 pos);
	virtual void update();

	// function for this program only
	void set_ball(GameObject * ball);

private:
	GameObject * ball;
	double angle_y_axis = 0;
	double angle_x_axis = 0;
};

