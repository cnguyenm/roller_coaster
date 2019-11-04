#pragma once
#include <pch.h>

class Spin;  // fix 2 class ref each other

class Ball :
	public GameObject
{
public:
	
	bool on_ground = false;
	bool on_track = true;  // if on_track, stick to track
	Camera * cam;
	Obstacle * obstacle;
	Spin * spin;
	Vec3 init_pos;  // pos when ball reset

	Ball();
	void set_cam(Camera * cam);
	void set_obstacle(Obstacle * obs);
	void set_track(Spin * spin);
	
	virtual void draw();
	virtual void update();  // called every DELTA_TIME

private:
	void apply_gravity();
	void apply_collision();
	void update_move();  // ODEs update
	Vec3 find_force(Hit hit);  // find force between obj, plane

	void run_on_track();
};

