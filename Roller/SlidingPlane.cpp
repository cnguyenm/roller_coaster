#include "pch.h"
#include "SlidingPlane.h"


SlidingPlane::SlidingPlane()
{
}

SlidingPlane::SlidingPlane(const std::vector<Vec3>& control_points) : control_points(control_points)
{
	color = _GREEN;
	find_direction();
}

bool SlidingPlane::is_collide(GameObject obj, Hit & hit)
{
	// just assume it collide
	hit.tangent = control_points[1] - control_points[0];

	return true;
}

double SlidingPlane::let_ball_run(double dist, Vec3& new_pos)
{
	// move ball along that dir
	double length = (control_points[1] - control_points[0]).magn();
	double delta_t = dist / length;

	double t1 = t0 + delta_t;
	if (t1 > 1) {
		new_pos = control_points[1];
		return (t1-1)*length;
	}
	else {
		new_pos = control_points[0] + t1 * length*direction;
		t0 = t1;
	}

	return 0;
}

void SlidingPlane::draw(Camera * cam)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	cam->apply();

		color.apply();
		glLineWidth(5.0f);
		glBegin(GL_LINES);
		for (Vec3 p : control_points) {
			glVertex3d(p.x, p.y, p.z);
		}
		glEnd();
		glLineWidth(1.0f);
	glPopMatrix();
}

void SlidingPlane::find_direction()
{
	direction = (control_points[1] - control_points[0]).normalized();
}

