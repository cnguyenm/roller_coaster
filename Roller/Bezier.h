#pragma once

#include <pch.h>

class Bezier : 
	public TrackComponent
{
public:
	
	std::vector<Vec3> control_points;
	std::vector<Vec3> control_line;
	std::vector<Vec3> points;
	Color color;
	int control_step = 9;
	double length;

	Bezier();
	Bezier(const std::vector<Vec3>& controls);

	void set_points(std::vector<Vec3> controls);
	void draw();
	virtual void draw(Camera * cam);
	void draw3d();
	Vec3 get_point_on_curve(double t);
	Vec3 get_derivative(double t);  // to get tangent at value t
	
	virtual double get_dist(Vec3 pos);   // get distance from a point
	virtual void set_start(Vec3 pos);
	virtual double let_ball_run(double dist, GameObject * obj);
	virtual double ball_run(double dist, GameObject * obj);
	virtual bool is_collide(GameObject obj, Hit & hit);

private:
	double t0 = 0;

	Vec3 interp(Vec3 n1, Vec3 n2, float lambda);
	void genControlLine();
	void genCurve();
	void find_length();

	static double BB(int n, int k, double t);
	static unsigned nChoosek(unsigned n, unsigned k);
};
