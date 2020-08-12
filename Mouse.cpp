#include "Mouse.h"
#include <GL/glut.h>

int buttons[3] = {0};
int mousex = 0;
int mousey = 0;


void Mouse::mousePress(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON)
		buttons[0] = state;
	else if(button == GLUT_MIDDLE_BUTTON)
		buttons[1] = state;
	else if(button == GLUT_RIGHT_BUTTON)
		buttons[2] = state;

	mousex = x;
	mousey = y;
}


void Mouse::mouseMove(int x, int y) {
	mousex = x;
	mousey = y;
}


void Mouse::warp(int x, int y) {
	glutWarpPointer(x, y);
}


bool Mouse::isButtonDown(int button) {
	if(button < 0 || button >= 3)
		return false;
	return buttons[button];
}


int Mouse::getx() {
	return mousex;
}


int Mouse::gety() {
	return  mousey;
}
