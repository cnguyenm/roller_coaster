#include "pch.h"
#include <iostream>

#include <gameshare.h>

int _edit_win;
Camera _edit_cam;
TeleportPoint tp_point1;

Ball _ball1;
SlidingPlane plane1;
SlidingPlane plane0, plane2, plane3;
Track real_track1;

extern GLUI *glui;

void update_edit_window() {
	glutSetWindow(_edit_win);
	glutPostRedisplay();
}

void rotate_cam(unsigned char key) {

	switch (key) {

		// cam rotate left, by rotate everything right 
		case 'a':			
			_edit_cam.rotate_around_yaxis(5); break;
		case 'd':
			_edit_cam.rotate_around_yaxis(-5); break;
		case 'w':
			_edit_cam.rotate_around_xaxis(5); break;
		case 's':
			_edit_cam.rotate_around_xaxis(-5); break;
		default:
			break;
	}
}

void move_cam(unsigned char key) {
	
	switch (key) {
		case 'a':
			_edit_cam.move_relative(-2,  0, 0); break;
			
		case 'd':
			_edit_cam.move_relative(2, 0, 0); break;
		case 'w':
			_edit_cam.move_relative(0, 0, -2); break;
		case 's':
			_edit_cam.move_relative(0, 0, 2); break;
		case 'r':
			_edit_cam.move_relative(0, 2, 0); break;
		case 'f':
			_edit_cam.move_relative(0, -2, 0); break;
		default:
			break;
	}
}

void handle_keyboard(unsigned char key, int x, int y) {

	//printf("%c \n", key);
	int mod = glutGetModifiers();
	if (mod == GLUT_ACTIVE_ALT) {
		rotate_cam(key);
	}
	else {
		move_cam(key);
	}
	
	update_edit_window();
}

void draw_axis() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// --- draw 
	glLoadIdentity();
	_edit_cam.apply();
	_WHITE.apply();

	glBegin(GL_LINES);
		
		for (double i = -10.0; i < 10.1; i += 2) {

			// x-z: x vector
			glVertex3d(-10.0, 0, i);
			glVertex3d( 10.0, 0, i);

			// x-z: z vector
			glVertex3d(i, 0, -10.0);
			glVertex3d(i, 0,  10.0);
		}

		// x
		//glVertex3f(0, 0, 0);
		//glVertex3f(5, 0, 0);

		//// y
		//glVertex3f(0, 0, 0);
		//glVertex3f(0, 5, 0);

		//// z
		//glVertex3f(0, 0, 0);
		//glVertex3f(0, 0, 5);
	glEnd();

	// --- /draw

	glPopMatrix();
}

void draw_gate() {

	

}

void draw_spin() {

	double radius = 5;
	double u = radius / 2 + sqrt(radius);
	double h = 0.5;

	// cylinder
	glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glLoadIdentity();

		// --- draw 
		_edit_cam.apply();

		glRotated(-90, 1, 0, 0);
		_WHITE.apply();
		glutWireCylinder(5.0f, 10.0f, 50, 20);  // radius=2, height=5


	glPopMatrix();

	// draw track
	real_track1.draw(&_edit_cam);
}

void reshape(int width, int height) {

	if (height == 0) height = 1; // prevent divide by 0
	double aspect = (double)width / (double)height;

	// set view port
	glViewport(0, 0, width, height);

	// set aspect ratio of clipping volumne to match viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// enble perspective projection 
	gluPerspective(45.0, aspect, 0.1f, 100.f);

}

void render_edit_win() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color buffer (background)
	glMatrixMode(GL_MODELVIEW);

	// render 
	draw_axis();
	_ball1.set_cam(&_edit_cam);
	_ball1.draw();
	
	// draw track
	draw_spin();

	glutSwapBuffers();
}

void design_track2() {

	double radius = 5;
	double u = radius / 2 + sqrt(radius);
	double h = 0.5;

	Bezier *curve1a = new Bezier({
		// x, height, y
		{  0,	0,   u},
		{u/2,	0,   u},
		{  u,	h, u/2},
		{  u, 2*h,   0}
	});

	Bezier *curve1b = new Bezier({
		{	u, 2*h,   0},
		{	u, 3*h, -u/2},
		{ u/2, 4*h, -u},
		{	0, 5*h, -u}
		}); 

	Bezier *curve1c = new Bezier({
		{   0, 5*h,   -u},
		{-u/2, 6*h,   -u},
		{  -u, 7*h, -u/2},
		{  -u, 8*h,    0}
	});

	Bezier *curve1d = new Bezier({
		{	-u,  8*h,   0},
		{	-u,  9*h, u/2},
		{ -u/2, 10*h,   u},
		{	 0, 11*h,   u}
	}); 

	Bezier *curve2a = new Bezier({
		{  0,	11*h,   u},
		{u/2,	12*h,   u},
		{  u,	13*h, u/2},
		{  u,	14*h,   0}
	});

	Bezier *curve2b = new Bezier({
		{	u, 14*h,    0},
		{	u, 15*h, -u/2},
		{ u/2, 16*h,   -u},
		{	0, 17*h,   -u}
	}); 

	Bezier * curve2c = new Bezier({
		{	0, 17*h, -u},
		{-u/2, 18*h, -u},
		{  -u, 19*h,-u/2},
		{  -u, 20*h,   0}
	});

	Bezier * curve2d = new Bezier({
		{  -u, 20*h,  0},
		{  -u, 21*h,u/2},
		{-u/2, 22*h,  u},
		{   0, 23*h,  u}
	});

	Bezier * curve3a = new Bezier({
		{  0, 23*h,  u},
		{u/2, 24*h,  u},
		{  u, 25*h,u/2},
		{  u, 26*h,  0}
	});

	Bezier * curve3b = new Bezier({
		{  u, 26*h,   0},
		{  u, 27*h,-u/2},
		{u/2, 28*h,  -u},
		{  0, 28*h,  -u}
	});

	curve1b->color = _GREEN;
	curve1d->color = _GREEN;
	curve2b->color = _GREEN;
	curve2d->color = _GREEN;
	curve3b->color = _GREEN;
	//curve3d->color = _GREEN;

	// set ball on spin
	SlidingPlane *p0 = new SlidingPlane({
		{-10, 28*h, -u},
		{  0, 28*h, -u}
	});
	p0->color = _YELLOW;

	SlidingPlane *p2 = new SlidingPlane({
		{-15, 32*h, -u },
		{-10, 28*h, -u}
	});

	SlidingPlane *p1 = new SlidingPlane({
		{ 0, 0, u},
		{-3, 0, u}
	});

	SlidingPlane *p3 = new SlidingPlane({
		{-3, 0, u},
		{-5, 0, u}
	});

	SlidingPlane *p4 = new SlidingPlane({
		{-5, 0, u},
		{-15, 10, u}
	});


	real_track1 = Track({
		p2, p0, 
		curve3b,curve3a,curve2d,curve2c,curve2b,curve2a,
		curve1d,curve1c,curve1b,curve1a,
		p1, p3, p4
	});
	p2->t0 = 0.2;

	_ball1.set_init_pos(Vec3(-15, 32*h + _ball1.size, -u));
	_ball1.set_track(&real_track1);
	_ball1.vel.x = 1;  // give ball a push
}

void init_gl() {
	glClearColor(0.0, 0.0, 0.0, 0); // set background to black
	glClearDepth(1.0f); // set background depth to farthest
	glEnable(GL_DEPTH_TEST); // enable depth test for z-culling
	
	glDepthFunc(GL_LEQUAL); // set type of depth test
	glShadeModel(GL_SMOOTH); // enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // nice perspective corrections
}

void init_game() {
	_edit_cam = Camera();
	_edit_cam.pos = Vec3(-10, 25, 30);
	
	// ball
	_ball1 = Ball();
	_ball1.size = 0.1;
	_ball1.set_init_pos(Vec3(-9, 8.5, 0));
	_ball1.set_cam(&_edit_cam);

	// tp point
	tp_point1 = TeleportPoint();
	tp_point1.set_target(&_ball1);
	tp_point1.set_init_pos(Vec3(16, 6, 0));
	tp_point1.destination = Vec3(-4, 6, 0);

	// design spin
	design_track2();
}

// test only
// no run in production
void update_edit_win(int value) {

	if (!_is_playing) return;

	glutSetWindow(_edit_win);

	_ball1.update();
	render_edit_win();

	

	glutTimerFunc(_DELTA_TIME, update_edit_win, 1);
}

void on_edit_close() {
	printf("[INFO] close display window\n");
	printf("[INFO] free objects\n");
	real_track1.free();
	_is_playing = false;
	glui->disable();
}

int main(int argc, char ** argv) {

	//test();
	// init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);	// enable double bufferd mode
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 50);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// create window
	_edit_win =  glutCreateWindow("Edit Window");
	glutReshapeFunc(reshape);
	glutDisplayFunc(render_edit_win);
	glutKeyboardFunc(handle_keyboard);
	
	// set window close, not exit program
	glutCloseFunc(on_edit_close);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// init
	init_gl();
	init_game();

	// gui
	build_glui(_edit_win);

	//update_edit_win(1);
	// start play_win, but not update yet

	glutMainLoop();
	return 0;

}