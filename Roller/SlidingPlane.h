#pragma once
#include "GameObject.h"
#include "gameshare.h"
class SlidingPlane :
	public TrackComponent
{
public:
	std::vector<Vec3> control_points;

	// for timebeing, let sliding plane have 2 points
	SlidingPlane();
	SlidingPlane(const std::vector<Vec3>& control_points);
	
	virtual bool is_collide(GameObject obj, Hit & hit);
	virtual double let_ball_run(double dist, Vec3& new_pos);
	virtual double ball_run(double dist, GameObject * obj);
	virtual void draw(Camera * cam);

	virtual double get_dist(Vec3 pos);  // get distance from a point

	virtual void set_start(Vec3 pos);

private:
	double t0 = 0.0;  // cur t
	double length;
	Vec3 direction;

	void find_length();
	void find_direction();
};

