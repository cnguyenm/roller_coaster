#include "pch.h"
#include "SlidingPlane.h"


SlidingPlane::SlidingPlane()
{
}

SlidingPlane::SlidingPlane(const std::vector<Vec3>& control_points) : control_points(control_points)
{
	color = _GREEN;
	find_length();
	find_direction();
}

bool SlidingPlane::is_collide(GameObject obj, Hit & hit)
{
	// just assume it collide
	hit.tangent = control_points[1] - control_points[0];

	return true;
}

double SlidingPlane::ball_run(double dist, GameObject * obj)
{
	// check if ball reverse direction
	Vec3 tangent = control_points[1] - control_points[0];
	Vec3 vel = obj->vel;
	double cos_a = tangent * vel;
	bool is_reverse = true;
	if (cos_a > 0) {
		is_reverse = false;
	}
	else {}

	// move ball
	double delta_t = dist / length;
	double t1;
	if (!is_reverse) {
		t1 = t0 + delta_t;
	}
	else {
		t1 = t0 - delta_t;
	}

	// see if it overshoot
	if (t1 > 1) {
		obj->pos = control_points[1];
		return (t1 - 1)*length;
	}
	// negative
	else if (t1 < 0) {
		obj->pos = control_points[0];
		return (-t1)*length;  
	}
	else {
		obj->pos = control_points[0] + t1 * length*direction;
		t0 = t1;
	}

	return 0.0;
}

void SlidingPlane::draw(Camera * cam)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	cam->apply();

		color.apply();
		glLineWidth(10.0f);
		glBegin(GL_LINES);
		for (Vec3 p : control_points) {
			glVertex3d(p.x, p.y, p.z);
		}
		glEnd();
		glLineWidth(1.0f);
	glPopMatrix();
}

double SlidingPlane::get_dist(Vec3 pos)
{
	// get smallest dist
	double dist1 = (control_points[0] - pos).magn();
	double dist2 = (control_points[1] - pos).magn();

	return fmin(dist1, dist2);
}

void SlidingPlane::set_start(Vec3 pos)
{
	double dist1 = (control_points[0] - pos).magn();
	double dist2 = (control_points[1] - pos).magn();
	
	if (dist1 < dist2) t0 = 0;
	else t0 = 1;
}

void SlidingPlane::find_length()
{
	length = (control_points[1] - control_points[0]).magn();
}

void SlidingPlane::find_direction()
{
	direction = (control_points[1] - control_points[0]).normalized();
}

