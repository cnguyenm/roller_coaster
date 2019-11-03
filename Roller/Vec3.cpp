#include "pch.h"


Vec3::Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;

}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z)
{
	// use that syntax, no need to do this
	//this->x = x;
	//this->y = y;
	//this->z = z;
}

Vec3 Vec3::operator+(Vec3 other)
{
	Vec3 result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	result.z = this->z + other.z;

	return result;
}

Vec3 Vec3::operator-(Vec3 other)
{
	Vec3 result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	result.z = this->z - other.z;

	return result;
}

Vec3 Vec3::operator*(double value)
{
	Vec3 result;
	result.x = this->x * value;
	result.y = this->y * value;
	result.z = this->z * value;

	return result;
}

Vec3 Vec3::operator/(double value)
{
	return Vec3(x/value, y/value, z/value);
}

double Vec3::operator*(Vec3 other)
{
	return x * other.x + y * other.y + z * other.z;
}

bool Vec3::operator==(Vec3 other)
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

Vec3 Vec3::cross(Vec3 other)
{
	Vec3 result;

	// x = y1z2 - y2z1
	result.x = y * other.z - other.y*z;

	// y = z1x2 - z2x1
	result.y = z * other.x - other.z*x;

	// z = x1y2 - x2y1
	result.z = x * other.y - other.x*y;

	return result;
}

Vec3& Vec3::operator+= (Vec3 b) {

	this->x = this->x + b.x;
	this->y = this->y + b.y;
	this->z = this->z + b.z;
	return *this;
}


double Vec3::magn()
{
	return sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}

Vec3 Vec3::normalized()
{
	double m = magn(); // magnitude
	return Vec3(x/m, y/m, z/m);
}

// a = Vec3()
// b = -a
Vec3 operator-(Vec3 other)
{
	return other * (-1);
}

Vec3 operator*(double v, Vec3 vec)
{
	return vec * v;
}
