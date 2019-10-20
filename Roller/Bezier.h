#pragma once

#include <pch.h>


class Bezier : 
	public GameObject, public Obstacle
{
public:
	Bezier();
	std::vector<Vec3> ctrl_points;
	Color color;

	// set list points
	void set_points(std::vector<Vec3> p_list);
	void draw();
	void draw3d();

	virtual bool is_collide(GameObject obj, Hit& hit);

	/*
	 * no push, pop matrix :(
	 * handle it outside for now
	 */
	static void draw_curve( 
		std::vector<Vec3> ctrl_points,
		Color color);

private:

	Vec3 get_point_on_curve(double t);
	Vec3 get_derivative(double t);  // to get tangent at value t
	static double BB(int n, int k, double t);
	static unsigned nChoosek(unsigned n, unsigned k);
};
