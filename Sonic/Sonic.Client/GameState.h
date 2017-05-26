#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Game.h"

class GameState
{
public:
	virtual void load(Game* game) = 0;
	virtual int unload() = 0;
	virtual void update(Game* game, float dt) = 0;
	virtual void render(Game* game) = 0;

	void changeState(Game* game, GameState* state) {
		game->changeState(state);
	}

protected:
	GameState() { }
};

#endif // !GAME_STATE_H
