#pragma once
#include <pch.h>

/*
 * contain list of sliding plane + bezier
 * render as: plane1, bezier1, plane2, bezier2,...
 */
class RollerTrack :
	public GameObject, public Obstacle
{
public:

	std::vector<Vec3> points;
	std::vector<Bezier> bezier_list;

	Camera * cam;

	RollerTrack();

	// add point relative to init_pos
	void add_point(Vec3 p);

	// set cam to render
	void set_cam(Camera * cam);

	// connect all lines with Bezier curve
	// called after creat, before draw
	void process_track();

	// override parent GameObject
	virtual void draw();

	// custom draw for 3d view
	virtual void draw3d();

	// override parent Obstacle
	virtual bool is_collide(GameObject obj, Hit& hit);

private:
	double max_left, max_right, max_top, max_down;
	void draw_arc(Vec3 p1, Vec3 p2, Vec3 p1_ext);
	void connect_line(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4);

	bool is_collide_line(int index, GameObject obj, Hit& out_hit);
};

