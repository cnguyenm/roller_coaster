
#include <pch.h>
#include <gameshare.h>

GLUI *glui;
GLUI_StaticText * game_msg;
void update_edit_win(int value);  // from source.cpp


enum GLUI_CUST_ID {
	ID_PLAY, ID_PAUSE, ID_RESET,
	ID_CLOSE_PLAY,
	ID_EXIT
};

void btn_play(int control) {
	printf("play\n");
	_is_playing = true;  // play.cpp use this

	update_edit_win(1);
	//if (_play_win == -1) start_play_window();
	//else update_play_win(1);


	//glutSetWindow(_play_win);
	//glutPostRedisplay();
}

void btn_pause(int control) {
	_is_playing = false;
}

// toggle between play/pause
void btn_toggle_play(int control) {

	// pause
	if (_is_playing) {
		_is_playing = false;
		return;
	}

	// play, or resume
	if (_edit_win == -1) {
		printf("Edit win already closed\n");
		return;
	}
	_is_playing = true;  // play.cpp use this
	update_edit_win(1);

	//if (_play_win == -1) start_play_window(); // if not window
	//else update_play_win(1);


	glutSetWindow(_edit_win);
	glutPostRedisplay();
}

void btn_reset_play(int control) {

}

void btn_close_play(int control) {

	_is_playing = false;
	glutDestroyWindow(_play_win);
	_play_win = -1;
}

void btn_exit(int control) {
	exit(1);
}

void build_glui(int display_win) {
	
	// setup
	//glui = GLUI_Master.create_glui_subwindow(display_win, GLUI_SUBWINDOW_RIGHT);
	glui = GLUI_Master.create_glui("GLUI", 0, 0, 0);

	// static text
	GLUI_Panel *panel_msg = new GLUI_Panel(glui, "Game message                              ", GLUI_PANEL_EMBOSSED);
	panel_msg->set_alignment(GLUI_ALIGN_LEFT);
	game_msg = new GLUI_StaticText(panel_msg, "To move edit_camera:");
	new GLUI_StaticText(panel_msg, "Use WASD for forward, left, back, right");
	new GLUI_StaticText(panel_msg, "Use RF for up, down");
	new GLUI_StaticText(panel_msg, "Use Alt + WASD to rotate");

	// other buttons
	GLUI_Panel * panel_op = new GLUI_Panel(glui, "Control");
	panel_op->set_alignment(GLUI_ALIGN_LEFT);
	new GLUI_Button(panel_op, "Play/Pause", ID_PLAY, btn_toggle_play);
	
	new GLUI_Button(panel_op, "Close Play", ID_CLOSE_PLAY, btn_close_play);
	new GLUI_Button(panel_op, "Exit", ID_EXIT, btn_exit);

}


