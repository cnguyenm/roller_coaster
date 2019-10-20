#include "pch.h"
#include <gameshare.h>


RollerTrack::RollerTrack()
{
	this->set_init_pos(Vec3(0, 0, 0));
	points = std::vector<Vec3>();
}

void RollerTrack::add_point(Vec3 p)
{
	this->points.push_back(p + this->init_pos);
}

void RollerTrack::set_cam(Camera * cam)
{
	this->cam = cam;
}

void RollerTrack::process_track()
{
	if (this->points.size() < 4) return;

	// add bezier curve
	for (int i = 2; i < points.size() -1; i += 2) {
		connect_line(
			points[i - 2], points[i - 1],
			points[i], points[i + 1]);
	}

	// find corner of track (for collision)
	this->max_left  =  10000;
	this->max_right = -10000;
	this->max_top	= -10000;
	this->max_down	=  10000;

	for (Vec3 p : points) {
		if (p.x < max_left	) max_left = p.x;
		if (p.x > max_right	) max_right = p.x;
		if (p.y > max_top	) max_top = p.y;
		if (p.y < max_down	) max_down = p.y;
	}
}

bool RollerTrack::is_collide(GameObject obj, Hit & out_hit)
{
	// check obj in Roller boundary
	if (obj.pos.x + obj.size < max_left  ||
		obj.pos.x - obj.size > max_right ||
		obj.pos.y - obj.size > max_top	 ||
		obj.pos.y + obj.size < max_down -0.5) {  // increase width of track, avoid fall through
		//printf("out of bounds\n");
		return false;
	}
		

	// find pair it collides 
	// maybe plane, bezier
	double start, end;
	double error = 0.1;
	int index1 = -1, index2;
	for (int i = 0; i < points.size()-1; i++) {

		start = fmin(points[i].x, points[i+1].x);
		end	  = fmax(points[i].x, points[i + 1].x);
		if ( (start <= obj.pos.x) && (obj.pos.x <= end+0.2) ) {
			index1 = i;
			index2 = i + 1;
			break;
		}
	}

	// if index1 even -> line
	// odd -> bezier
	if (index1 == -1) return false;

	if (index1 % 2 == 0) {
		return is_collide_line(index1, obj, out_hit);
	}
	else {
		//printf("bezier, p_index=%d\n", (index1 - 1) / 2);
		Bezier bezier = bezier_list[(index1 - 1)/2];
		bool ret = bezier.is_collide(obj, out_hit);
		if (!ret) {
			//printf("not bezier\n");
		}
		return ret;
	}
	
	return false;
}

void RollerTrack::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	this->cam->apply();

	// --- draw 
	
	int i = 0;

	// draw lines
	while(i<points.size()-1) {

		// lines
		glBegin(GL_LINES);
		_GREEN.apply();			
			glVertex3d(points[i].x, points[i].y, points[i].z);
			glVertex3d(points[i+1].x, points[i+1].y, points[i+1].z);
		glEnd();

		i += 2;
	}

	// draw bezier
	for (Bezier b : bezier_list) {
		b.draw();
	}
	
	// --- /draw
	glPopMatrix();
}

void RollerTrack::draw3d()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	this->cam->apply();

	// --- draw 
	// draw lines
	int i = 0;
	while (i < points.size() - 1) {

		// lines
		_GREEN.apply();
		//glBegin(GL_LINES);		
		//	glVertex3d(points[i].x, points[i].y, points[i].z);
		//	glVertex3d(points[i + 1].x, points[i + 1].y, points[i + 1].z);

		//	// additional 2 lines
		//	glVertex3d(points[i].x, points[i].y, points[i].z -0.25);
		//	glVertex3d(points[i + 1].x, points[i + 1].y, points[i + 1].z-0.25);

		//	glVertex3d(points[i].x, points[i].y, points[i].z + 0.25);
		//	glVertex3d(points[i + 1].x, points[i + 1].y, points[i + 1].z + 0.25);		
		//glEnd();

		glBegin(GL_QUADS);
			glVertex3d(points[i].x, points[i].y, points[i].z + 0.25);
			glVertex3d(points[i + 1].x, points[i + 1].y, points[i + 1].z + 0.25);
			glVertex3d(points[i + 1].x, points[i + 1].y, points[i + 1].z - 0.25);
			glVertex3d(points[i].x, points[i].y, points[i].z - 0.25);
		glEnd();

		i += 2;
	}

	// draw bezier
	for (Bezier b : bezier_list) {
		b.draw3d();
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

	//Bezier::draw_curve(cam, ctrl_points, _YELLOW);
	Bezier bezier = Bezier();
	bezier.set_points(ctrl_points);
	this->bezier_list.push_back(bezier);
}

bool RollerTrack::is_collide_line(int index, GameObject obj, Hit & out_hit)
{
	Vec3 p1 = points[index];
	Vec3 p2 = points[index + 1];

	// formula for line: y=ax+b
	// => a = (y1-y2) / (x1-x2)
	double a = (p1.y - p2.y) / (p1.x - p2.x);

	// b = y1 - ax1
	double b = p1.y - a * p1.x;

	// find hit point: line x=x0, and y=ax+b
	// => y' = ax0+b
	// hit = (x0, hit_y)
	double hit_y = a * obj.pos.x + b;
	Vec3 hit_pos = Vec3(obj.pos.x, hit_y, 0);

	// check dist
	double error = 0.01;
	double dist = (obj.pos - hit_pos).magn();
	if (dist > obj.size + error)return false;

	// find tangent
	// -----------

	Vec3 tangent = (p1 - p2).normalized();
	out_hit.pos = hit_pos;
	out_hit.tangent = tangent;

	return true;
}


