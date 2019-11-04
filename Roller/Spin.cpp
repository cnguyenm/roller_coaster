#include "pch.h"
#include "Spin.h"
#include "gameshare.h"

Spin::Spin()
{
}

Spin::Spin(const std::vector<Bezier>& curve_list) : curve_list(curve_list)
{
	find_boundary();
}

void Spin::add_curve(Bezier curve)
{
	this->curve_list.push_back(curve);
}

void Spin::set_cam(Camera * cam)
{
	this->cam = cam;
}

bool Spin::let_ball_run(double dist, Vec3& out_pos)
{
	double delta_t = dist / curve_list[cur_curve_index].length;
	double t1 = cur_t - delta_t;  // descending, at top, t=1
	//printf("delta_t=%.2f ,t1=%d \n",delta_t, t1);

	if (t1 < 0.0) {		
		double remain_dist = (-t1) * curve_list[cur_curve_index].length;
		cur_t = 1;
		cur_curve_index -= 1;
		printf("swich to curve [%d]\n", cur_curve_index);

		// if out of curve
		if (cur_curve_index < 0) {
			return false;
		}

		return let_ball_run(remain_dist, out_pos);
	}
	else {
		cur_t = t1;
		out_pos = curve_list[cur_curve_index].get_point_on_curve(t1);
	}

	return true;
}

void Spin::draw()
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();

	// --- draw 
	cam->apply();
	bool color = true;

	for (Bezier curve : curve_list) {

		if (color) _GREEN.apply();
		else _RED.apply();

		curve.draw();
		color = !color;
	}


	glPopMatrix();
}

bool Spin::is_collide(GameObject obj, Hit & hit)
{
	if (obj.pos.x - obj.size > upper_right.x ||
		obj.pos.y - obj.size > upper_right.y ||
		obj.pos.z + obj.size < upper_right.z) return false;

	if (obj.pos.x < bottom_left.x ||
		obj.pos.y < bottom_left.y ||
		obj.pos.z > bottom_left.z) return false;

	// find collision point (or t)
	hit.pos = curve_list[cur_curve_index].get_point_on_curve(cur_t);

	// find direction
	hit.tangent = curve_list[cur_curve_index].get_derivative(cur_t);

	return true;
}

void Spin::find_boundary()
{
	
	for (Bezier curve : curve_list) {
		Vec3 p0 = curve.control_points[0];
		Vec3 p1 = curve.control_points[3];

		if (p0.x > upper_right.x) upper_right.x = p0.x;
		if (p0.y > upper_right.y) upper_right.y = p0.y;
		if (p0.z < upper_right.z) upper_right.z = p0.z;

		if (p0.x < bottom_left.x) bottom_left.x = p0.x;
		if (p0.y < bottom_left.y) bottom_left.y = p0.y;
		if (p0.z > bottom_left.z) bottom_left.z = p0.z;

		if (p1.x > upper_right.x) upper_right.x = p1.x;
		if (p1.y > upper_right.y) upper_right.y = p1.y;
		if (p1.z < upper_right.z) upper_right.z = p1.z;

		if (p1.x < bottom_left.x) bottom_left.x = p1.x;
		if (p1.y < bottom_left.y) bottom_left.y = p1.y;
		if (p1.z > bottom_left.z) bottom_left.z = p1.z;
	}

	printf("upper right: %.2f, %.2f, %.2f\n", upper_right.x, upper_right.y, upper_right.z);
	printf("bottom left: %.2f, %.2f, %.2f\n", bottom_left.x, bottom_left.y, bottom_left.z);

}


