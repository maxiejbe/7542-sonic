#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "GameState.h"
#include <iostream>
#include "Texture.h"
#include "InputManager.h"
#include "MenuState.h"
#include "utils/PlayerUtils.h"


class GameOverState : public GameState {
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static GameOverState* Instance() {
		return &m_GameOverState;
	}

protected:
	GameOverState() {}

private:
	static GameOverState m_GameOverState;
	Texture gameOverBackground;

	void showGameOver();
};

#endif // !GAME_OVER_STATE_H