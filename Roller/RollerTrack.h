#pragma once
#include <pch.h>

class RollerTrack :
	public GameObject
{
public:

	std::vector<Vec3> points;
	Camera * cam;

	RollerTrack();
	void add_point(Vec3 p);
	void set_cam(Camera * cam);
	virtual void draw();

private:
	void draw_arc(Vec3 p1, Vec3 p2, Vec3 p1_ext);
	void connect_line(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4);
};

