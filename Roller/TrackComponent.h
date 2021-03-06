#pragma once
class TrackComponent : public GameObject
{
public:
	double t0 = 0.0;  // cur t
	TrackComponent();
	
	virtual bool is_collide(GameObject obj, Hit & hit) { return false; };
	
	// should return remain_dist
	virtual double ball_run(double dist, GameObject * obj) { return 0; }

	virtual double get_dist(Vec3 pos) {return 0; }  // get distance from a point

	virtual void set_start(Vec3 pos) {}  // set start point, so component know t=1 or 0
};

