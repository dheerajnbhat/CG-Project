#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <iostream>
#include "GameStateManager.h"
#include "PlayState.h"
#include "Keyboard.h"
#include "Mouse.h"

#define MAX_FPS 60

GameStateManager stateManager;
PlayState playState;
Keyboard keyboard;
Mouse mouse;


void init() {
	stateManager.setState(&playState);
}


void update(void) {
	stateManager.update();
}


void render(void) {
	stateManager.render();
}


void mainLoop(int value) {
	update();
	render();
	glutTimerFunc(1000/MAX_FPS, mainLoop, value);
}


void changeSize(int w, int h) {
	stateManager.changeSize(w, h);
}


void keyboardDown(unsigned char key, int x, int y) {
	keyboard.setKeyDown(key);
	stateManager.keyboardDown(key, x, y);
}


void keyboardUp(unsigned char key, int x, int y) {
	keyboard.setKeyUp(key);
	stateManager.keyboardUp(key, x, y);
}


void mouseMove(int x, int y) {
	mouse.mouseMove(x, y);
	stateManager.mouseMove(x, y);
}


void mousePress(int button, int state, int x, int y) {
	mouse.mousePress(button, state, x, y);
	mouseMove(x, y);
	stateManager.mousePress(button, state, x, y);
}


int main(int argc, char **argv) {
	stateManager.addState(&playState);

	glutInit(&argc, argv);
	system("kill `ps | grep 'aplay'|awk '{print $1}'`") ;	// stop any previous background music
	system("aplay background.wav&") ;			// play sound

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(1500, 250);
	glutInitWindowSize(1200, 600);
	glutCreateWindow("3D Maze");
	GLenum error = glewInit();

	if (error != GLEW_OK) {
		printf("Error starting GLEW: %s\n", glewGetErrorString(error));
		exit(0);
	}

	glutTimerFunc(1000/MAX_FPS, mainLoop, 0);
	glutDisplayFunc(render);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mousePress);
	glutPassiveMotionFunc(mouseMove);
	init();
	
	glutMainLoop();
}
