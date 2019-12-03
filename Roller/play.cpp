
#include <pch.h>

#include <gameshare.h>

int _play_win = -1;
Camera _play_cam;

// define in source.cpp
extern Ball _ball1;
extern RollerTrack track1;
extern RollerTrack track2;
extern TeleportPoint tp_point1;
extern Track real_track1;

double _playcam_fov = 50.0;
int play_width;
int play_height;

void render_edit_win();  // define in source.cpp

void draw_axis2() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// --- draw 
	glLoadIdentity();
	_play_cam.apply();
	_WHITE.apply();

	glBegin(GL_LINES);

	for (double i = -30.0; i < 30.1; i += 2) {

		// x-z: x vector
		glVertex3d(-30.0, 0, i);
		glVertex3d(30.0, 0, i);

		// x-z: z vector
		glVertex3d(i, 0, -30.0);
		glVertex3d(i, 0, 30.0);
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


void reshape2(int width, int height) {

	if (height == 0) height = 1; // prevent divide by 0
	double aspect = (double)width / (double)height;

	// set view port
	glViewport(0, 0, width, height);
	play_width = width;
	play_height = height;
	
	// set aspect ratio of clipping volumne to match viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// enble perspective projection 
	gluPerspective(_playcam_fov, aspect, 0.1f, 100.f);

}

void reshape_play_win() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// enble perspective projection 
	double aspect = (double)play_width / (double)play_height;
	gluPerspective(_playcam_fov, aspect, 0.1f, 100.f);
}

void render_play_win() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color buffer (background)
	
	// perspective
	reshape_play_win();

	glMatrixMode(GL_MODELVIEW);

	// render 
	
	_ball1.set_cam(&_play_cam);
	//track1.set_cam(&_play_cam);
	//track2.set_cam(&_play_cam);

	//_play_cam.pos = _ball1.pos;
	//_play_cam.pos.y += _ball1.size;
	//_play_cam.pos.x += _ball1.size/2;
	//_play_cam.look_at(_play_cam.pos + Vec3(1, -1, 0));

	draw_axis2();
	_ball1.draw();
	real_track1.draw(&_play_cam);
	//track1.draw();
	//track1.draw3d();
	//track2.draw3d();

	glutSwapBuffers();
}

void init_gl2() {
	glClearColor(0.0, 0.0, 0.0, 0); // set background to black
	glClearDepth(1.0f); // set background depth to farthest
	glEnable(GL_DEPTH_TEST); // enable depth test for z-culling

	glDepthFunc(GL_LEQUAL); // set type of depth test
	glShadeModel(GL_SMOOTH); // enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // nice perspective corrections
}

void init_game2() {
	_play_cam = Camera();
	_play_cam.pos = Vec3(0, 1, 10);

	_play_cam.set_ball(&_ball1);
	_play_cam.update();
}

void update_play_win(int value) {

	if (!_is_playing) return;

	// update objects
	_ball1.update();
	//tp_point1.update();
	_play_cam.update();  // auto-update ball on track
	
	// edit win
	glutSetWindow(_edit_win);
	render_edit_win();

	// play win
	glutSetWindow(_play_win);
	render_play_win();

	
	glutTimerFunc(_DELTA_TIME, update_play_win, 1);
}

void reset_play() {

	// pause game
	_is_playing = false;

	// reset obj
	_ball1.reset_pos();
	_ball1.vel = Vec3(0.5, -0.2, 0);  // so camera knows where to look

	_play_cam.update();
	real_track1.reset();

	// re-display
	// edit win
	glutSetWindow(_edit_win);
	render_edit_win();

	// play win
	glutSetWindow(_play_win);
	render_play_win();


}

int start_play_window() {

	// init
	glutInitDisplayMode(GLUT_DOUBLE);	// enable double bufferd mode
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// window
	_play_win = glutCreateWindow("Play Window");
	//printf("play win: %d\n", _play_win);
	glutReshapeFunc(reshape2);
	glutDisplayFunc(render_play_win);

	init_gl2();
	init_game2();

	// call every DELTA_TIME
	update_play_win(1);

	return 1;
}