#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "GameState.h"
#include <vector>
#include <iostream>

class GameStateManager {
	private:
		std::vector<GameState*> states;
		GameState *currentState;

	public:
		GameStateManager();

		void addState(GameState *state);
		void deleteState(GameState *state);
		void setState(GameState *state);

		void update();
		void render();
		void changeSize(int w, int h);
		void keyboardDown(unsigned char key, int x, int y);
		void keyboardUp(unsigned char key, int x, int y);
		void mousePress(int button, int state, int x, int y);
		void mouseMove(int x, int y);
};

#endif
