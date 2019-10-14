#pragma once

#include <pch.h>


class Bezier
{
public:
	Bezier();
	
	static void draw_curve(Camera*cam, 
		std::vector<Vec3> ctrl_points,
		Color color);

private:
	static double BB(int n, int k, double t);
	static unsigned nChoosek(unsigned n, unsigned k);
};

