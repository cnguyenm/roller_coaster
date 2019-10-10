#include "pch.h"
#include <iostream>

Camera _edit_cam;
Color _GREEN = Color(0, 1, 0);
Color _WHITE = Color(1, 1, 1);

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

		// --- draw 
		glLoadIdentity();
		_edit_cam.apply();

		_GREEN.apply();
		glTranslatef(0, 0.5, 0);  // position of cube_center
		glutWireCube(1);
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
	draw_cube();


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
	_edit_cam.pos = Vec3(15, 15, 15);
}

int main(int argc, char ** argv) {

	//test();


	// init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);	// enable double bufferd mode
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// create window
	glutCreateWindow("Roller Coaster");
	glutReshapeFunc(reshape);
	glutDisplayFunc(render_scene);
	
	// init
	init_gl();
	init_game();

	glutMainLoop();
	return 0;

}