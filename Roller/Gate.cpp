#include "pch.h"
#include "Gate.h"
#include "gameshare.h"

Gate::Gate()
{
}

void Gate::set_cam(Camera *cam)
{
	this->cam = cam;
}

void Gate::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	cam->apply();

	// --- draw 
	// position counter-clock wise, with normal pointing out
	// for lighting
	glBegin(GL_QUADS);

	// left
		_BLUE.apply();
		glVertex3d(-w / 2, 0, 0);
		glVertex3d(-w / 2, h, 0);
		glVertex3d(-w / 2, h, -d);
		glVertex3d(-w / 2, 0, -d);

		// right
		_YELLOW.apply();
		glVertex3d(w / 2, 0, -d);
		glVertex3d(w / 2, h, -d);
		glVertex3d(w / 2, h, 0);
		glVertex3d(w / 2, 0, 0);

		// top
		_RED.apply();
		glVertex3d(w / 2, h, 0);
		glVertex3d(w / 2, h, -d);
		glVertex3d(-w / 2, h, -d);
		glVertex3d(-w / 2, h, 0);

	glEnd();
	// --- /draw
	glPopMatrix();
}

