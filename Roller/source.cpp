#include "pch.h"
#include <iostream>

#include <gameshare.h>

int _edit_win;
Camera _edit_cam;
Gate gate1;
RollerTrack track1;
Ball _ball1;

void update_edit_window() {
	glutSetWindow(_edit_win);
	glutPostRedisplay();
}

void handle_keyboard(unsigned char key, int x, int y) {

	//printf("%c \n", key);
	switch (key)
	{
	case 'a':
		_edit_cam.move_left(2); break;
	case 'd':
		_edit_cam.move_right(2); break;
	case 'w':
		_edit_cam.move_up(2); break;		
	case 's':
		_edit_cam.move_down(2); break;
	default:
		break;
	}
	update_edit_window();
}


inline void draw_axis() {

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

inline void draw_cube() {

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

inline void draw_gate() {

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

inline void reshape(int width, int height) {

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

inline void render_scene() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color buffer (background)
	glMatrixMode(GL_MODELVIEW);

	// render 
	draw_axis();
	//draw_cube();
	//draw_gate();
	//GameObject * obj = &gate1;
	//obj->draw();
	//draw_line();
	track1.draw();
	_ball1.draw();

	glutSwapBuffers();
}

inline void init_gl() {
	glClearColor(0.0, 0.0, 0.0, 0); // set background to black
	glClearDepth(1.0f); // set background depth to farthest
	glEnable(GL_DEPTH_TEST); // enable depth test for z-culling
	
	glDepthFunc(GL_LEQUAL); // set type of depth test
	glShadeModel(GL_SMOOTH); // enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // nice perspective corrections
}

inline void init_game() {
	_edit_cam = Camera();
	//_edit_cam.pos = Vec3(15, 15, 15);
	_edit_cam.pos = Vec3(0, 5, 40);
	//_edit_cam.pos = Vec3(0, 1, 10);  // position of play_cam, maybe
	
	gate1 = Gate();
	gate1.set_cam(&_edit_cam);

	track1 = RollerTrack();
	track1.set_cam(&_edit_cam);
	track1.add_point(Vec3(-10, 8, 0));
	track1.add_point(Vec3( -1, 6, 0));

	track1.add_point(Vec3(  3, 4, 0));
	track1.add_point(Vec3(  6, 2, 0));

	track1.add_point(Vec3(  9, 2, 0));
	track1.add_point(Vec3(  12, 4, 0));

	track1.add_point(Vec3(  15, 6, 0));
	track1.add_point(Vec3(  19, 6, 0));
	track1.process_track();

	_ball1 = Ball();
	_ball1.size = 0.25;
	_ball1.pos = Vec3(-5, 8, 0);
	_ball1.set_cam(&_edit_cam);
	_ball1.set_obstacle(&track1);
}

// test only
// no run in production
void update_edit_win(int value) {

	glutSetWindow(_edit_win);

	_ball1.update();
	render_scene();

	glutTimerFunc(_DELTA_TIME, update_edit_win, 1);
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
	glutDisplayFunc(render_scene);
	glutKeyboardFunc(handle_keyboard);

	// set window close, not exit program
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// init
	init_gl();
	init_game();

	// gui
	build_glui(_edit_win);

	update_edit_win(1);

	glutMainLoop();
	return 0;

}