#pragma once
#include <pch.h>

class Spin;  // fix 2 class ref each other
class SlidingPlane;

class Ball :
	public GameObject
{
public:
	
	bool on_ground = false;
	bool on_track = true;  // if on_track, stick to track
	Camera * cam;
	Track * track;
	
	Ball();
	void set_cam(Camera * cam);
	void set_track(Track * track);
	
	virtual void draw();
	virtual void update();  // called every DELTA_TIME
	void reset_pos();

private:
	void apply_gravity();
	void update_move();  // ODEs update
	Vec3 find_force(Hit hit);  // find force between obj, plane
	void run_on_track();
};

