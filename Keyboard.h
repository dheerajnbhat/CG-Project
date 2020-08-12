#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard {
	public:
		void setKeyDown(unsigned char key);
		void setKeyUp(unsigned char key);
		bool isDown(unsigned char key);
};

#endif
