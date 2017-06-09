#ifndef END_LEVEL_STATE_H
#define END_LEVEL_STATE_H

#include "GameState.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "InputManager.h"
#include "MenuState.h"

class EndLevelState : public GameState {
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static EndLevelState* Instance() {
		return &m_EndLevelState;
	}

protected:
	EndLevelState() {}

private:
	static EndLevelState m_EndLevelState;

	Player* player;
	TTF_Font* fontLifes;
	TTF_Font* fontScore;
	TTF_Font* fontLevel;
	Texture levelHasPassed;

	void showLevelHasPassed();
	void showStatistics();
	void showText(string text, int x, int y, TTF_Font* font, SDL_Color color);
	void freeSurfaceStatistics();
	void showPlayerImage(Texture playerImage, int x, int y);

};

#endif // !END_LEVEL_STATE_H