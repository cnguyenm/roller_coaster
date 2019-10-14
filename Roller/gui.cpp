
#include <pch.h>
#include <gameshare.h>

GLUI *glui;
GLUI_StaticText * game_msg;

enum GLUI_CUST_ID {
	ID_PLAY,
	ID_CLOSE_PLAY,
	ID_EXIT
};

void btn_play(int control) {
	printf("play\n");
	start_play_window();

	glutSetWindow(_play_win);
	glutPostRedisplay();
}

void btn_close_play(int control) {

	glutDestroyWindow(_play_win);
}

void btn_exit(int control) {
	exit(1);
}

void build_glui(int display_win) {

	// setup
	//glui = GLUI_Master.create_glui_subwindow(display_win, GLUI_SUBWINDOW_RIGHT);
	glui = GLUI_Master.create_glui("GLUI", 0, 0, 0);

	// static text
	GLUI_Panel *panel_msg = new GLUI_Panel(glui, "Game message");                              
	panel_msg->set_alignment(GLUI_ALIGN_LEFT);
	game_msg = new GLUI_StaticText(panel_msg, "Empty message");
	//new GLUI_StaticText(panel3, "Change param before running");

	// other buttons
	GLUI_Panel * panel_op = new GLUI_Panel(glui, "Control", GLUI_PANEL_EMBOSSED);
	panel_op->set_alignment(GLUI_ALIGN_LEFT);
	new GLUI_Button(panel_op, "Play", ID_PLAY, btn_play);
	new GLUI_Button(panel_op, "Close Play", ID_CLOSE_PLAY, btn_close_play);
	new GLUI_Button(panel_op, "Exit", ID_EXIT, btn_exit);

}