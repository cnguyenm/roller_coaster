#pragma once

#include <pch.h>


class Bezier : 
	public GameObject, public Obstacle
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

	// set list points
	void set_points(std::vector<Vec3> p_list);
	void draw();
	void draw3d();
	Vec3 get_point_on_curve(double t);
	Vec3 get_derivative(double t);  // to get tangent at value t
	virtual bool is_collide(GameObject obj, Hit& hit);

	/*
	 * no push, pop matrix :(
	 * handle it outside for now
	 */
	static void draw_curve( std::vector<Vec3> ctrl_points, Color color);

private:

	Vec3 interp(Vec3 n1, Vec3 n2, float lambda);
	void genControlLine();
	void genCurve();
	void find_length();

	
	
	static double BB(int n, int k, double t);
	static unsigned nChoosek(unsigned n, unsigned k);
};
