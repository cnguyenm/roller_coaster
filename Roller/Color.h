#pragma once

#include "GL/glut.h"

class Color
{
public:
	Color();
	Color(double r, double g, double b);
	double red;
	double green;
	double blue;

	void apply();
};

