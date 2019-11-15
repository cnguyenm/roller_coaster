#pragma once
class TrackComponent : public GameObject
{
public:
	TrackComponent();
	
	virtual bool is_collide(GameObject obj, Hit & hit) { return false; };
	
	// should return remain_dist
	virtual double let_ball_run(double dist, Vec3& new_pos) { return 0; };

	virtual double ball_run(double dist, GameObject * obj) { return 0; }

	virtual double get_dist(Vec3 pos) {return 0; }  // get distance from a point

	virtual void set_start(Vec3 pos) {}  // set start point, so component know t=1 or 0
};

