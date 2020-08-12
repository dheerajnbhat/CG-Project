#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState {
	public:
		virtual void enter() = 0;
		virtual void leave() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void changeSize(int w, int h) = 0;
		virtual void keyboardDown(unsigned char key, int x, int y) = 0;
		virtual void keyboardUp(unsigned char key, int x, int y) = 0;
		virtual void mousePress(int button, int state, int x, int y) = 0;
		virtual void mouseMove(int x, int y) = 0;
};

#endif
