
#include <pch.h>

#include <gameshare.h>

int _play_win;
Camera _play_cam;


void draw_axis2() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// --- draw 
	glLoadIdentity();
	_play_cam.apply();
	_WHITE.apply();

	glBegin(GL_LINES);

	for (double i = -10.0; i < 10.1; i += 2) {

		// x-z: x vector
		glVertex3d(-10.0, 0, i);
		glVertex3d(10.0, 0, i);

		// x-z: z vector
		glVertex3d(i, 0, -10.0);
		glVertex3d(i, 0, 10.0);
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

inline void draw_gate() {

	double h = 3.0;  // height
	double w = 6.0;  // width
	double d = 4.0;  // depth
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	_play_cam.apply();
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

inline void render_scene2() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color buffer (background)
	glMatrixMode(GL_MODELVIEW);

	// render 
	draw_axis2();


	glutSwapBuffers();
}

inline void init_gl2() {
	glClearColor(0.0, 0.0, 0.0, 0); // set background to black
	glClearDepth(1.0f); // set background depth to farthest
	glEnable(GL_DEPTH_TEST); // enable depth test for z-culling

	glDepthFunc(GL_LEQUAL); // set type of depth test
	glShadeModel(GL_SMOOTH); // enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // nice perspective corrections
}

inline void init_game2() {
	_play_cam = Camera();
	_play_cam.pos = Vec3(0, 1, 10);
}

int start_play_window() {

	// init
	glutInitDisplayMode(GLUT_DOUBLE);	// enable double bufferd mode
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// window
	_play_win = glutCreateWindow("Play Window");
	glutReshapeFunc(reshape);
	glutDisplayFunc(render_scene2);

	init_gl2();
	init_game2();

	return 1;
}