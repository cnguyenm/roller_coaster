#pragma once
class Vec3
{
public:

	double x, y, z;
	Vec3();
	Vec3(double x, double y, double z);
	
	Vec3 operator + (Vec3 other);
	Vec3 operator - (Vec3 other);
	Vec3 operator * (double value);
	Vec3 operator / (double value);
	double operator * (Vec3 other);  // dot product
	bool operator == (Vec3 other);

	// c += a
	Vec3& operator+= (Vec3 b);

	// get magnitude of vector
	double magn();

	// reduce vector to unit_length
	Vec3 normalized();

	friend Vec3 operator - (Vec3 other);
	friend Vec3 operator * (double v, Vec3 vec);
};

