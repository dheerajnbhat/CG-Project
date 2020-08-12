#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
	private:

	public:
		void mousePress(int button, int state, int x, int y);
		void mouseMove(int x, int y);
		void warp(int x, int y);
		bool isButtonDown(int button);
		int getx();
		int gety();
};

#endif
