#include "pch.h"
#include "RollerTrack.h"
#include <gameshare.h>


RollerTrack::RollerTrack()
{
	points = std::vector<Vec3>();
}

void RollerTrack::add_point(Vec3 p)
{
	this->points.push_back(p);
}

void RollerTrack::set_cam(Camera * cam)
{
	this->cam = cam;
}

void RollerTrack::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	this->cam->apply();

	// --- draw 
	
	int i = 0;

	while(i<points.size()-1) {

		// lines
		glBegin(GL_LINES);
		_GREEN.apply();			
			glVertex3d(points[i].x, points[i].y, points[i].z);
			glVertex3d(points[i+1].x, points[i+1].y, points[i+1].z);
		glEnd();

		// todo: connect 1st line, 2nd line
		if (i >= 2) {
			connect_line(points[i - 2], points[i - 1],
				points[i], points[i + 1]);
		}

		i += 2;
	}

	
	// --- /draw
	glPopMatrix();
}

void RollerTrack::draw_arc(Vec3 p1, Vec3 p2, Vec3 p1_ext)
{
	// default: 60 degree
	double alpha = 60;  

	// find angle beta
	double beta = 90 - alpha / 2;
	beta = beta / 180 * _PI;  // degree->radian
	double dist = (p2 - p1).magn();
	double r = (dist / 2) / cos(beta);

	// find side of center
	// center, p1_ext must be on diff side of line p1p2



	// draw arc

}

void RollerTrack::connect_line(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4)
{
	// line1
	Vec3 p1p2 = (p2 - p1).normalized();
	Vec3 p2_ext = p2 + p1p2;

	Vec3 p3p4 = (p4 - p3).normalized();
	Vec3 p3_pre = p3 - p3p4;

	std::vector<Vec3> ctrl_points = std::vector<Vec3>();
	ctrl_points.push_back(p2);
	ctrl_points.push_back(p2_ext);
	ctrl_points.push_back(p3_pre);
	ctrl_points.push_back(p3);

	Bezier::draw_curve(cam, ctrl_points, _YELLOW);
}


