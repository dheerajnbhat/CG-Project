#include "Keyboard.h"

bool keyStates[256] = {false};

void Keyboard::setKeyDown(unsigned char key) {
	keyStates[key] = true;
}

void Keyboard::setKeyUp(unsigned char key) {
	keyStates[key] = false;
}

bool Keyboard::isDown(unsigned char key) {
	return keyStates[key];
}
