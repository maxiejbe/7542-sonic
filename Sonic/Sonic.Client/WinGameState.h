#ifndef END_GAME_STATE_H
#define END_GAME_STATE_H

#include "GameState.h"
#include <iostream>
#include "Texture.h"
#include "InputManager.h"
#include "MenuState.h"
#include "utils/PlayerUtils.h"

class WinGameState : public GameState {
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static WinGameState* Instance() {
		return &m_WinGameState;
	}

protected:
	WinGameState() {}

private:
	static WinGameState m_WinGameState;
	Texture winGameBackground;

	void showWinGame();
};

#endif // !END_GAME_STATE_H