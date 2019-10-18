#pragma once
#include <pch.h>

class Ball :
	public GameObject
{
public:
	
	bool on_ground = false;
	Camera * cam;
	Obstacle * obstacle;

	Ball();
	void set_cam(Camera * cam);
	void set_obstacle(Obstacle * obs);

	virtual void draw();
	virtual void update();  // called every DELTA_TIME

private:
	void apply_gravity();
	void apply_collision();
	void update_move();  // ODEs update
	Vec3 find_force(Hit hit);  // find force between obj, plane
};

