#pragma once
class TrackComponent : public GameObject
{
public:
	TrackComponent();
	
	virtual bool is_collide(GameObject obj, Hit & hit) { return false; };
	
	// should return remain_dist
	virtual double let_ball_run(double dist, Vec3& new_pos) { return 0; };
};

