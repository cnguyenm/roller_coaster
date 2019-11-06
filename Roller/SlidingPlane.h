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

	virtual void draw(Camera * cam);

private:
	double t0 = 0.0;  // cur t
	Vec3 direction;

	void find_direction();
};

