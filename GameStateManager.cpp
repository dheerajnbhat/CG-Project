#include "GameStateManager.h"

GameStateManager::GameStateManager() {
	currentState = nullptr;
}

void GameStateManager::addState(GameState *state) {
	states.push_back(state);
}

void GameStateManager::deleteState(GameState *state) {
	if(state == currentState) // you can't delete the current state
		std::cerr << "Cannot delete current state from state manager.\n";
	else
		for(int i = 0; i < states.size(); ++i)
			if(states[i] == state)
				states.erase(states.begin()+i);
}

void GameStateManager::setState(GameState *state) {
	if(currentState != nullptr)
		currentState->leave();
	currentState = state;
	currentState->enter();
}

void GameStateManager::update() {
	currentState->update();
}

void GameStateManager::render() {
	currentState->render();
}

void GameStateManager::changeSize(int w, int h) {
	currentState->changeSize(w, h);
}

void GameStateManager::keyboardDown(unsigned char key, int x, int y) {
	currentState->keyboardDown(key, x, y);
}

void GameStateManager::keyboardUp(unsigned char key, int x, int y) {
	currentState->keyboardUp(key, x, y);
}

void GameStateManager::mousePress(int button, int state, int x, int y) {
	currentState->mousePress(button, state, x, y);
}

void GameStateManager::mouseMove(int x, int y) {
	currentState->mouseMove(x, y);
}
