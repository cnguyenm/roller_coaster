#include "pch.h"

Color::Color()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}

Color::Color(double r, double g, double b)
{
	this->red = r;
	this->green = g;
	this->blue = b;
}

void Color::apply()
{
	glColor3d(red, green, blue);
}


