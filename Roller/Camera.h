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

	// move to pos, also affect camera_center
	void move_to(Vec3 pos);
};

