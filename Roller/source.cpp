#include "pch.h"
#include <iostream>

#include <gameshare.h>

int _edit_win;
Camera _edit_cam;
Gate gate1;
RollerTrack track1;
RollerTrack track2;
TeleportPoint tp_point1;

Ball _ball1;

Bezier _curve_test1;
RollerTrack track_test1;

Spin spin1;
SlidingPlane plane1;
SlidingPlane plane0, plane2, plane3;
Bezier b1;
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

void draw_ground() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// --- draw 
	glLoadIdentity();
	_edit_cam.apply();
	_GREY.apply();
	glBegin(GL_QUADS);
		glVertex3d(-10, 0, 10);
		glVertex3d( 10, 0, 10);
		glVertex3d( 10, 0, -10);
		glVertex3d( -10, 0, -10);
	glEnd();
	glPopMatrix();
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

void draw_cube() {

	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glLoadIdentity();

		// --- draw 
		_edit_cam.apply();

		_GREEN.apply();
		glTranslatef(0, 0.5, 0);  // position of cube_center
		glutWireCube(1);
		// --- /draw

	glPopMatrix();
}

void draw_gate() {

	double h = 3.0;  // height
	double w = 6.0;  // width
	double d = 4.0;  // depth
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	_edit_cam.apply();
	// --- draw 
	// position counter-clock wise, with normal pointing out
	// for lighting
	glBegin(GL_QUADS);

		// left
		_BLUE.apply();
		glVertex3d(-w/2, 0, 0);
		glVertex3d(-w/2, h, 0);
		glVertex3d(-w/2, h, -d);
		glVertex3d(-w/2, 0, -d);

		// right
		_YELLOW.apply();
		glVertex3d(w/2, 0, -d);
		glVertex3d(w/2, h, -d);
		glVertex3d(w/2, h, 0);
		glVertex3d(w/2, 0, 0);

		// top
		_RED.apply();
		glVertex3d(w/2, h, 0);
		glVertex3d(w/2, h, -d);
		glVertex3d(-w/2, h, -d);
		glVertex3d(-w/2, h, 0);

	glEnd();
	// --- /draw
	glPopMatrix();

}

void draw_line() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	_edit_cam.apply();


	// --- draw 
	
	glBegin(GL_LINES);
	_GREEN.apply();

		//1st line
		glVertex3d(-10, 3, 0);
		glVertex3d(  3, 3, 0);

		//2nd line
		glVertex3d(5, 2, 0);
		glVertex3d(8, 0, 0);
	glEnd();

	// --- /draw
	glPopMatrix();
}

void draw_test_curve() {
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	_edit_cam.apply();

	_curve_test1.draw3d();

	glPopMatrix();
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


	// draw lines
	//glMatrixMode(GL_MODELVIEW);

	//	glPushMatrix();
	//	glLoadIdentity();

	//	// --- draw 
	//	_edit_cam.apply();

	//		
	//	// draw lines
	//	_GREEN.apply();
	//	glLineWidth(5.0f);
	//	glBegin(GL_LINES);
	//		glVertex3d(0, 16 * h, -u);
	//		glVertex3d(-10, 16 * h, -u);
	//	glEnd();
	//	glLineWidth(1.0f);

	//glPopMatrix();


	// draw spin
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
	//draw_ground();
	draw_axis();
	//draw_cube();
	//draw_gate();
	//GameObject * obj = &gate1;
	//obj->draw();
	//draw_line();
	//track1.set_cam(&_edit_cam);
	//track2.set_cam(&_edit_cam);
	_ball1.set_cam(&_edit_cam);
	//track_test1.set_cam(&_edit_cam);

	//track1.draw3d();
	//track2.draw3d();
	_ball1.draw();
	//draw_test_curve();
	//track_test1.draw3d();

	draw_spin();

	glutSwapBuffers();
}

void design_roller_track() {

	// --- track1 ---
	// -------
	track1 = RollerTrack();
	track1.set_cam(&_edit_cam);
	track1.set_init_pos(Vec3(0, 0, 0));

	// slide for ball to gain vel
	track1.add_point(Vec3(-10, 8, 0));
	track1.add_point(Vec3(-7, 7, 0));

	track1.add_point(Vec3(-5, 6, 0));
	track1.add_point(Vec3(-1, 6, 0));

	track1.add_point(Vec3(3, 4, 0));
	track1.add_point(Vec3(6, 2, 0));

	track1.add_point(Vec3(9, 2, 0));
	track1.add_point(Vec3(12, 4, 0));

	track1.add_point(Vec3(15, 6, 0));
	track1.add_point(Vec3(19, 6, 0));
	track1.process_track();

	// --- track2 ---
	// -------
	track2 = RollerTrack();
	track2.set_cam(&_edit_cam);
	track2.set_init_pos(Vec3(20, 0, 0));

	// overlap 1st horizontal of track1
	track2.add_point(Vec3(-5, 6, 0));
	track2.add_point(Vec3(-1, 6, 0));

	track2.add_point(Vec3(3, 4, 0));
	track2.add_point(Vec3(6, 2, 0));

	track2.add_point(Vec3(9, 2, 0));
	track2.add_point(Vec3(12, 4, 0));

	track2.add_point(Vec3(15, 6, 0));
	track2.add_point(Vec3(19, 6, 0));
	track2.process_track();
}

void design_track2() {

	double radius = 5;
	double u = radius / 2 + sqrt(radius);
	double h = 0.5;

	Bezier *curve1 = new Bezier({
		// x, height, y
		{  0,	0,   u},
		{u/2,	0,   u},
		{  u,	h, u/2},
		{  u, 2*h,   0}
	});

	Bezier *curve2 = new Bezier({
		{	u, 2*h,   0},
		{	u, 3*h, -u/2},
		{ u/2, 4*h, -u},
		{	0, 5*h, -u}
		}); 

	Bezier *curve3 = new Bezier({
		{   0, 5*h,   -u},
		{-u/2, 6*h,   -u},
		{  -u, 7*h, -u/2},
		{  -u, 8*h,    0}
	});

	Bezier *curve4 = new Bezier({
		{	-u,  8*h,   0},
		{	-u,  9*h, u/2},
		{ -u/2, 10*h,   u},
		{	 0, 11*h,   u}
	}); 

	Bezier *curve5 = new Bezier({
		{  0,	11*h,   u},
		{u/2,	12*h,   u},
		{  u,	13*h, u/2},
		{  u,	14*h,   0}
	});

	Bezier *curve6 = new Bezier({
		{	u, 14*h,    0},
		{	u, 15*h, -u/2},
		{ u/2, 16*h,   -u},
		{	0, 16*h,   -u}
	}); 

	curve2->color = _GREEN;
	curve4->color = _GREEN;
	curve6->color = _GREEN;

	// set ball on spin
	SlidingPlane *p0 = new SlidingPlane({
		{-10, 16 * h, -u},
		{  0, 16 * h, -u}
	});

	SlidingPlane *p2 = new SlidingPlane({
		{-15, 19 * h, -u },
		{-10, 16 * h, -u}
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
		{-9, 5, u}
	});


	real_track1 = Track({
		p2, p0, 
		curve6, curve5, curve4, curve3, curve2, curve1, 
		p1, p3, p4
	});

	_ball1.set_init_pos(Vec3(-10, 16 * h + _ball1.size, -u));
	_ball1.set_track(&real_track1);
	_ball1.vel.x = 1;  // give ball a push
}

void design_track() {

	plane0 = SlidingPlane({
		{-5, 5, 0},
		{-1, 1, 0}
	});

	plane1 = SlidingPlane({
		{1, 1, 0},
		{5, 5, 0}
	});

	b1 = Bezier({
		{-1, 1, 0},
		{ 0, 0, 0},
		{ 0, 0, 0},
		{ 1, 1, 0}
	});

	real_track1 = Track({
		&plane0, &b1, &plane1
	});

	_ball1.set_track(&real_track1);
	plane0.t0 = 0.2;

	//_ball1.vel.x = 1;  // give ball a push
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
	_edit_cam.pos = Vec3(0, 10, 20);
	//_edit_cam.pos = Vec3(0, 5, 40);
	//_edit_cam.pos = Vec3(0, 1, 10);  // position of play_cam, maybe
	
	gate1 = Gate();
	gate1.set_cam(&_edit_cam);

	// roller track
	design_roller_track();

	// ball
	_ball1 = Ball();
	_ball1.size = 0.25;
	_ball1.set_init_pos(Vec3(-9, 8.5, 0));
	_ball1.set_cam(&_edit_cam);
	_ball1.set_obstacle(&track1);

	// tp point
	tp_point1 = TeleportPoint();
	tp_point1.set_target(&_ball1);
	tp_point1.set_init_pos(Vec3(16, 6, 0));
	tp_point1.destination = Vec3(-4, 6, 0);


	// bezier 3d, space curve
	_curve_test1 = Bezier();
	std::vector<Vec3> p_list1;
	p_list1.push_back(Vec3(-2, 5, 2));
	p_list1.push_back(Vec3(3, 5, 2));
	p_list1.push_back(Vec3(3, 1, 6));
	p_list1.push_back(Vec3(3, 1, 12));
	
	_curve_test1.set_points(p_list1);
	track_test1 = RollerTrack();
	track_test1.set_cam(&_edit_cam);
	track_test1.set_init_pos(Vec3(0, 0, 0));

	// slide for ball to gain vel
	track_test1.add_point(Vec3(-2, 5, 2));
	track_test1.add_point(Vec3(3, 5, 2));

	track_test1.add_point(Vec3(3, 1, 4));
	track_test1.add_point(Vec3(3, 1, 8));

	// design spin
	//design_spin();
	design_track();
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