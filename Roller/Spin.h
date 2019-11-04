#pragma once
#include "pch.h"


class Spin :
	public GameObject
{
public:
	
	std::vector<Bezier> curve_list;
	Camera * cam;

	Spin();
	Spin(const std::vector<Bezier>& curve_list);
	void add_curve(Bezier curve);
	void set_cam(Camera * cam);
	//void set_ball(Ball * ball);
	bool let_ball_run(double dist, Vec3& out_pos);


	virtual void draw();
	virtual bool is_collide(GameObject obj, Hit& hit);

private:
	Vec3 upper_right;
	Vec3 bottom_left;
	double cur_t = 1.0;
	int cur_curve_index = 5; // hard code for now

	void find_boundary();
};

